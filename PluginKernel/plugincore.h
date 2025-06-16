// -----------------------------------------------------------------------------
//    ASPiK Plugin Kernel File:  plugincore.h
//
/**
    \file   plugincore.h
    \author Will Pirkle
    \date   17-September-2018
    \brief  base class interface file for ASPiK plugincore object
    		- http://www.aspikplugins.com
    		- http://www.willpirkle.com
*/
// -----------------------------------------------------------------------------
#ifndef __pluginCore_h__
#define __pluginCore_h__

#include "pluginbase.h"
#include "fxobjects.h"
#include <fl\Headers.h>
using namespace fl;
// **--0x7F1F--**

// --- Plugin Variables controlID Enumeration 

enum controlID {
	volume = 0,
	boostCut = 1,
	boostCut1 = 10,
	boostCut2 = 11,
	boostCut3 = 12,
	boostCut4 = 13,
	boostCut5 = 14,
	r_Led = 3,
	boostCut6 = 15,
	boostCut7 = 16,
	boostCut8 = 17,
	boostCut9 = 18,
	boostCut10 = 19,
	eqPreset = 4,
	xCoord = 5,
	yCoord = 6,
	l_Led = 7,
	fuzzyLed = 20
};

	// **--0x0F1F--**

/**
\class PluginCore
\ingroup ASPiK-Core
\brief
The PluginCore object is the default PluginBase derived object for ASPiK projects.
Note that you are fre to change the name of this object (as long as you change it in the compiler settings, etc...)


PluginCore Operations:
- overrides the main processing functions from the base class
- performs reset operation on sub-modules
- processes audio
- processes messages for custom views
- performs pre and post processing functions on parameters and audio (if needed)

\author Will Pirkle http://www.willpirkle.com
\remark This object is included in Designing Audio Effects Plugins in C++ 2nd Ed. by Will Pirkle
\version Revision : 1.0
\date Date : 2018 / 09 / 7
*/
class PluginCore : public PluginBase
{
public:
    PluginCore();

	/** Destructor: empty in default version */
    virtual ~PluginCore(){}

	// --- PluginBase Overrides ---
	//
	/** this is the creation function for all plugin parameters */
	bool initPluginParameters();

	/** called when plugin is loaded, a new audio file is playing or sample rate changes */
	virtual bool reset(ResetInfo& resetInfo);

	/** one-time post creation init function; pluginInfo contains path to this plugin */
	virtual bool initialize(PluginInfo& _pluginInfo);

	// --- preProcess: sync GUI parameters here; override if you don't want to use automatic variable-binding
	virtual bool preProcessAudioBuffers(ProcessBufferInfo& processInfo);

	/** process frames of data */
	virtual bool processAudioFrame(ProcessFrameInfo& processFrameInfo);

	// --- uncomment and override this for buffer processing; see base class implementation for
	//     help on breaking up buffers and getting info from processBufferInfo
	//virtual bool processAudioBuffers(ProcessBufferInfo& processBufferInfo);

	/** preProcess: do any post-buffer processing required; default operation is to send metering data to GUI  */
	virtual bool postProcessAudioBuffers(ProcessBufferInfo& processInfo);

	/** called by host plugin at top of buffer proccess; this alters parameters prior to variable binding operation  */
	virtual bool updatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo);

	/** called by host plugin at top of buffer proccess; this alters parameters prior to variable binding operation  */
	virtual bool updatePluginParameterNormalized(int32_t controlID, double normalizedValue, ParameterUpdateInfo& paramInfo);

	/** this can be called: 1) after bound variable has been updated or 2) after smoothing occurs  */
	virtual bool postUpdatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo);

	/** this is ony called when the user makes a GUI control change */
	virtual bool guiParameterChanged(int32_t controlID, double actualValue);

	/** processMessage: messaging system; currently used for custom/special GUI operations */
	virtual bool processMessage(MessageInfo& messageInfo);

	/** processMIDIEvent: MIDI event processing */
	virtual bool processMIDIEvent(midiEvent& event);

	/** specialized joystick servicing (currently not used) */
	virtual bool setVectorJoystickParameters(const VectorJoystickData& vectorJoysickData);

	/** create the presets */
	bool initPluginPresets();

	// --- BEGIN USER VARIABLES AND FUNCTIONS -------------------------------------- //
	//	   Add your variables and methods here
	

	//Fuzzy logic part --------------------------------------	

	void fuzzyEQUpdate(double x, double y);
	void fuzzyEQUpdate2(double x, double y);
	void fuzzyEQUpdate3(double x, double y);
	void fuzzyEQUpdate4(double x, double y);
	void fuzzyEQUpdate5(double x, double y);
	void fuzzyEQUpdate6(double x, double y);
	void fuzzyEQUpdate7(double x, double y);
	void fuzzyEQUpdate8(double x, double y);
	void fuzzyEQUpdate9(double x, double y);
	void fuzzyEQUpdate10(double x, double y);

	/*	DJD ------------------------------------------------------------------------	*/
protected:
	//10 array EQ Stereo
	AudioFilter f1_AudioFilter[2];
	AudioFilter f2_AudioFilter[2];
	AudioFilter f3_AudioFilter[2];
	AudioFilter f4_AudioFilter[2];
	AudioFilter f5_AudioFilter[2];
	AudioFilter f6_AudioFilter[2];
	AudioFilter f7_AudioFilter[2];
	AudioFilter f8_AudioFilter[2];
	AudioFilter f9_AudioFilter[2];

	AudioFilter f10_AudioFilter[2];
	void updateParameters();

	double constantQ = 1.414;
	double f_1 = 32;
	double f_2 = 64;
	double f_3 = 125;
	double f_4 = 250;
	double f_5 = 500;
	double f_6 = 1000;
	double f_7 = 2000;
	double f_8 = 4000;
	double f_9 = 8000;
	double f_10 = 16000;

	
	
	
	/*  DJD ------------------------------------------------------------------------    */


	// --- END USER VARIABLES AND FUNCTIONS -------------------------------------- //

private:
	//  **--0x07FD--**

	// --- Continuous Plugin Variables 
	double volume = 0.0;
	double boostCut = 0.0;
	double boostCut1 = 0.0;
	double boostCut2 = 0.0;
	double boostCut3 = 0.0;
	double boostCut4 = 0.0;
	double boostCut5 = 0.0;
	double boostCut6 = 0.0;
	double boostCut7 = 0.0;
	double boostCut8 = 0.0;
	double boostCut9 = 0.0;
	double boostCut10 = 0.0;
	float xCoord = 0.f;
	float yCoord = 0.f;

	// --- Discrete Plugin Variables 
	int eqPreset = 0;
	enum class eqPresetEnum { Classica,Dance,Pop,Reggae,Rock,Metal,Club,Party,Flat,Custom };	// to compare: if(compareEnumToInt(eqPresetEnum::Classica, eqPreset)) etc... 

	int fuzzyLed = 0;
	enum class fuzzyLedEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(fuzzyLedEnum::SWITCH_OFF, fuzzyLed)) etc... 

	// --- Meter Plugin Variables
	float r_Led = 0.f;
	float l_Led = 0.f;

	// **--0x1A7F--**
    // --- end member variables

public:
	//double boostCut1_prev = 0.0;
    /** static description: bundle folder name

	\return bundle folder name as a const char*
	*/
    static const char* getPluginBundleName();

    /** static description: name

	\return name as a const char*
	*/
    static const char* getPluginName();

	/** static description: short name

	\return short name as a const char*
	*/
	static const char* getShortPluginName();

	/** static description: vendor name

	\return vendor name as a const char*
	*/
	static const char* getVendorName();

	/** static description: URL

	\return URL as a const char*
	*/
	static const char* getVendorURL();

	/** static description: email

	\return email address as a const char*
	*/
	static const char* getVendorEmail();

	/** static description: Cocoa View Factory Name

	\return Cocoa View Factory Name as a const char*
	*/
	static const char* getAUCocoaViewFactoryName();

	/** static description: plugin type

	\return type (FX or Synth)
	*/
	static pluginType getPluginType();

	/** static description: VST3 GUID

	\return VST3 GUID as a const char*
	*/
	static const char* getVSTFUID();

	/** static description: 4-char code

	\return 4-char code as int
	*/
	static int32_t getFourCharCode();

	/** initalizer */
	bool initPluginDescriptors();

};




#endif /* defined(__pluginCore_h__) */
