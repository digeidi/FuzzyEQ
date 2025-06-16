// -----------------------------------------------------------------------------
//    ASPiK Plugin Kernel File:  plugincore.cpp
//
/**
    \file   plugincore.cpp
    \author Will Pirkle
    \date   17-September-2018
    \brief  Implementation file for PluginCore object
    		- http://www.aspikplugins.com
    		- http://www.willpirkle.com
*/
// -----------------------------------------------------------------------------
#include "plugincore.h"
#include "plugindescription.h"
#include <fl\Headers.h>
#include <string.h>

//Variabili globali Trackpad
float xActual = 0;
float yActual = 0;
//Variabili globali risultato motori fuzzy
float f1Fuzzy = 0;
float f2Fuzzy = 0;
float f3Fuzzy = 0;
float f4Fuzzy = 0;
float f5Fuzzy = 0;
float f6Fuzzy = 0;
float f7Fuzzy = 0;
float f8Fuzzy = 0;
float f9Fuzzy = 0;
float f10Fuzzy = 0;
//Variabile globale bool per Custom Preset
bool isCustom = false;

//double *f1_valAttuale = & boostCut1;
/**
\brief PluginCore constructor is launching pad for object initialization

Operations:
- initialize the plugin description (strings, codes, numbers, see initPluginDescriptors())
- setup the plugin's audio I/O channel support
- create the PluginParameter objects that represent the plugin parameters (see FX book if needed)
- create the presets
*/
PluginCore::PluginCore()
{
    // --- describe the plugin; call the helper to init the static parts you setup in plugindescription.h
    initPluginDescriptors();

    // --- default I/O combinations
	// --- for FX plugins
	if (getPluginType() == kFXPlugin)
	{
		addSupportedIOCombination({ kCFMono, kCFMono });
		addSupportedIOCombination({ kCFMono, kCFStereo });
		addSupportedIOCombination({ kCFStereo, kCFStereo });
	}
	else // --- synth plugins have no input, only output
	{
		addSupportedIOCombination({ kCFNone, kCFMono });
		addSupportedIOCombination({ kCFNone, kCFStereo });
	}

	// --- for sidechaining, we support mono and stereo inputs; auxOutputs reserved for future use
	addSupportedAuxIOCombination({ kCFMono, kCFNone });
	addSupportedAuxIOCombination({ kCFStereo, kCFNone });

	// --- create the parameters
    initPluginParameters();

    // --- create the presets
    initPluginPresets();
}

/**
\brief create all of your plugin parameters here

\return true if parameters were created, false if they already existed
*/
bool PluginCore::initPluginParameters()
{
	if (pluginParameterMap.size() > 0)
		return false;

    // --- Add your plugin parameter instantiation code bewtween these hex codes
	// **--0xDEA7--**


	// --- Declaration of Plugin Parameter Objects 
	PluginParameter* piParam = nullptr;

	// --- continuous control: Gain
	piParam = new PluginParameter(controlID::volume, "Gain", "dB", controlVariableType::kDouble, -12.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&volume, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: f_1000
	piParam = new PluginParameter(controlID::boostCut, "f_1000", "dB", controlVariableType::kDouble, -20.000000, 20.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&boostCut, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: f_1
	piParam = new PluginParameter(controlID::boostCut1, "f_1", "", controlVariableType::kDouble, -20.000000, 20.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&boostCut1, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: f_2
	piParam = new PluginParameter(controlID::boostCut2, "f_2", "", controlVariableType::kDouble, -20.000000, 20.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&boostCut2, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: f_3
	piParam = new PluginParameter(controlID::boostCut3, "f_3", "", controlVariableType::kDouble, -20.000000, 20.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&boostCut3, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: f_4
	piParam = new PluginParameter(controlID::boostCut4, "f_4", "", controlVariableType::kDouble, -20.000000, 20.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&boostCut4, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: f_5
	piParam = new PluginParameter(controlID::boostCut5, "f_5", "", controlVariableType::kDouble, -20.000000, 20.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&boostCut5, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- meter control: R
	piParam = new PluginParameter(controlID::r_Led, "R", 10.00, 100.00, ENVELOPE_DETECT_MODE_RMS, meterCal::kLogMeter);
	piParam->setBoundVariable(&r_Led, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- continuous control: f_6
	piParam = new PluginParameter(controlID::boostCut6, "f_6", "", controlVariableType::kDouble, -20.000000, 20.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&boostCut6, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: f_7
	piParam = new PluginParameter(controlID::boostCut7, "f_7", "", controlVariableType::kDouble, -20.000000, 20.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&boostCut7, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: f_8
	piParam = new PluginParameter(controlID::boostCut8, "f_8", "", controlVariableType::kDouble, -20.000000, 20.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&boostCut8, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: f_9
	piParam = new PluginParameter(controlID::boostCut9, "f_9", "", controlVariableType::kDouble, -20.000000, 20.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&boostCut9, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: f_10
	piParam = new PluginParameter(controlID::boostCut10, "f_10", "", controlVariableType::kDouble, -20.000000, 20.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&boostCut10, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: Presets
	piParam = new PluginParameter(controlID::eqPreset, "Presets", "Classica,Dance,Pop,Reggae,Rock,Metal,Club,Party,Flat,Custom", "Flat");
	piParam->setBoundVariable(&eqPreset, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: X
	piParam = new PluginParameter(controlID::xCoord, "X", "mm", controlVariableType::kFloat, 0.000000, 100.000000, 50.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&xCoord, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- continuous control: Y
	piParam = new PluginParameter(controlID::yCoord, "Y", "%", controlVariableType::kFloat, -10.000000, 10.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&yCoord, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: L
	piParam = new PluginParameter(controlID::l_Led, "L", 10.00, 100.00, ENVELOPE_DETECT_MODE_RMS, meterCal::kLogMeter);
	piParam->setBoundVariable(&l_Led, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- discrete control: Fuzzy
	piParam = new PluginParameter(controlID::fuzzyLed, "Fuzzy", "SWITCH OFF,SWITCH ON", "SWITCH ON");
	piParam->setBoundVariable(&fuzzyLed, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- Aux Attributes
	AuxParameterAttribute auxAttribute;

	// --- RAFX GUI attributes
	// --- controlID::volume
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::volume, auxAttribute);

	// --- controlID::boostCut
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::boostCut, auxAttribute);

	// --- controlID::boostCut1
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::boostCut1, auxAttribute);

	// --- controlID::boostCut2
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::boostCut2, auxAttribute);

	// --- controlID::boostCut3
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::boostCut3, auxAttribute);

	// --- controlID::boostCut4
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::boostCut4, auxAttribute);

	// --- controlID::boostCut5
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::boostCut5, auxAttribute);

	// --- controlID::r_Led
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::r_Led, auxAttribute);

	// --- controlID::boostCut6
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::boostCut6, auxAttribute);

	// --- controlID::boostCut7
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::boostCut7, auxAttribute);

	// --- controlID::boostCut8
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::boostCut8, auxAttribute);

	// --- controlID::boostCut9
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::boostCut9, auxAttribute);

	// --- controlID::boostCut10
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::boostCut10, auxAttribute);

	// --- controlID::eqPreset
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(805306368);
	setParamAuxAttribute(controlID::eqPreset, auxAttribute);

	// --- controlID::xCoord
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::xCoord, auxAttribute);

	// --- controlID::yCoord
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::yCoord, auxAttribute);

	// --- controlID::l_Led
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::l_Led, auxAttribute);

	// --- controlID::fuzzyLed
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741829);
	setParamAuxAttribute(controlID::fuzzyLed, auxAttribute);


	// **--0xEDA5--**
   
    // --- BONUS Parameter
    // --- SCALE_GUI_SIZE
    PluginParameter* piParamBonus = new PluginParameter(SCALE_GUI_SIZE, "Scale GUI", "tiny,small,medium,normal,large,giant", "normal");
    addPluginParameter(piParamBonus);

	// --- create the super fast access array
	initPluginParameterArray();

    return true;
}

/**
\brief initialize object for a new run of audio; called just before audio streams

Operation:
- store sample rate and bit depth on audioProcDescriptor - this information is globally available to all core functions
- reset your member objects here

\param resetInfo structure of information about current audio format

\return true if operation succeeds, false otherwise
*/
bool PluginCore::reset(ResetInfo& resetInfo)
{
    // --- save for audio processing
    audioProcDescriptor.sampleRate = resetInfo.sampleRate;
    audioProcDescriptor.bitDepth = resetInfo.bitDepth;

	//******** DJD
	//engine->setName("FuzzyTouchPad");
	//engine->setName("FuzzyTouchPad");
	//engine->setDescription("Motore Fuzzy GEQ");

	f1_AudioFilter[0].reset(resetInfo.sampleRate);
	f1_AudioFilter[1].reset(resetInfo.sampleRate);
	f2_AudioFilter[0].reset(resetInfo.sampleRate);
	f2_AudioFilter[1].reset(resetInfo.sampleRate);
	f3_AudioFilter[0].reset(resetInfo.sampleRate);
	f3_AudioFilter[1].reset(resetInfo.sampleRate);
	f4_AudioFilter[0].reset(resetInfo.sampleRate);
	f4_AudioFilter[1].reset(resetInfo.sampleRate);
	f5_AudioFilter[0].reset(resetInfo.sampleRate);
	f5_AudioFilter[1].reset(resetInfo.sampleRate);
	//******** DJD

    // --- other reset inits
    return PluginBase::reset(resetInfo);
}

/**
\brief one-time initialize function called after object creation and before the first reset( ) call

Operation:
- saves structure for the plugin to use; you can also load WAV files or state information here
*/
bool PluginCore::initialize(PluginInfo& pluginInfo)
{
	// --- add one-time init stuff here

	return true;
}

/**
\brief do anything needed prior to arrival of audio buffers

Operation:
- syncInBoundVariables when preProcessAudioBuffers is called, it is *guaranteed* that all GUI control change information
  has been applied to plugin parameters; this binds parameter changes to your underlying variables
- NOTE: postUpdatePluginParameter( ) will be called for all bound variables that are acutally updated; if you need to process
  them individually, do so in that function
- use this function to bulk-transfer the bound variable data into your plugin's member object variables

\param processInfo structure of information about *buffer* processing

\return true if operation succeeds, false otherwise
*/
bool PluginCore::preProcessAudioBuffers(ProcessBufferInfo& processInfo)
{
    // --- sync internal variables to GUI parameters; you can also do this manually if you don't
    //     want to use the auto-variable-binding
    syncInBoundVariables();

    return true;
}

/**
\brief frame-processing method

Operation:
- decode the plugin type - for synth plugins, fill in the rendering code; for FX plugins, delete the if(synth) portion and add your processing code
- note that MIDI events are fired for each sample interval so that MIDI is tightly sunk with audio
- doSampleAccurateParameterUpdates will perform per-sample interval smoothing

\param processFrameInfo structure of information about *frame* processing

\return true if operation succeeds, false otherwise
*/
bool PluginCore::processAudioFrame(ProcessFrameInfo& processFrameInfo)
{
	updateParameters();
    // --- fire any MIDI events for this sample interval
    processFrameInfo.midiEventQueue->fireMidiEvents(processFrameInfo.currentFrame);

	// --- do per-frame updates; VST automation and parameter smoothing
	doSampleAccurateParameterUpdates();

    // --- decode the channelIOConfiguration and process accordingly
	
	double finalVolume = pow(10.0, volume / 12.0);

	//Inputs
	//double xnL = processFrameInfo.audioInputFrame[0];
	//double xnR = processFrameInfo.audioInputFrame[1];

	float inputs[2] = { processFrameInfo.audioInputFrame[0], processFrameInfo.audioInputFrame[1] };

	//double ynL = f1_AudioFilter[0].processAudioSample(inputs[0]);
	//double ynR = f1_AudioFilter[0].processAudioSample(inputs[1]);

	//R,L Outputs
	double ynL = f1_AudioFilter[0].processAudioSample(f2_AudioFilter[0].processAudioSample(f3_AudioFilter[0].processAudioSample(f4_AudioFilter[0].processAudioSample(f5_AudioFilter[0].processAudioSample(f6_AudioFilter[0].processAudioSample(f7_AudioFilter[0].processAudioSample(f8_AudioFilter[0].processAudioSample(f9_AudioFilter[0].processAudioSample(f10_AudioFilter[0].processAudioSample(inputs[0]))))))))));
	double ynR = f1_AudioFilter[1].processAudioSample(f2_AudioFilter[1].processAudioSample(f3_AudioFilter[1].processAudioSample(f4_AudioFilter[1].processAudioSample(f5_AudioFilter[1].processAudioSample(f6_AudioFilter[1].processAudioSample(f7_AudioFilter[1].processAudioSample(f8_AudioFilter[1].processAudioSample(f9_AudioFilter[1].processAudioSample(f10_AudioFilter[1].processAudioSample(inputs[1]))))))))));

    // --- FX Plugin:
    if(processFrameInfo.channelIOConfig.inputChannelFormat == kCFMono &&
       processFrameInfo.channelIOConfig.outputChannelFormat == kCFMono)
    {
		// --- pass through code: change this with your signal processing2
        processFrameInfo.audioOutputFrame[0] = finalVolume * ynL;
		l_Led = processFrameInfo.audioOutputFrame[0];
		r_Led = processFrameInfo.audioOutputFrame[0];

        return true; /// processed
    }

    // --- Mono-In/Stereo-Out
    else if(processFrameInfo.channelIOConfig.inputChannelFormat == kCFMono &&
       processFrameInfo.channelIOConfig.outputChannelFormat == kCFStereo)
    {
		// --- pass through code: change this with your signal processing
        processFrameInfo.audioOutputFrame[0] = finalVolume * ynL;
        processFrameInfo.audioOutputFrame[1] = finalVolume * ynL;

		l_Led = processFrameInfo.audioOutputFrame[0];
		r_Led = processFrameInfo.audioOutputFrame[1];

        return true; /// processed
    }

    // --- Stereo-In/Stereo-Out
    else if(processFrameInfo.channelIOConfig.inputChannelFormat == kCFStereo &&
       processFrameInfo.channelIOConfig.outputChannelFormat == kCFStereo)
    {
		// --- pass through code: change this with your signal processing
        processFrameInfo.audioOutputFrame[0] = finalVolume * ynL;
        processFrameInfo.audioOutputFrame[1] = finalVolume * ynR;

		l_Led = processFrameInfo.audioOutputFrame[0];
		r_Led = processFrameInfo.audioOutputFrame[1];

        return true; /// processed
    }

    return false; /// NOT processed
}


/**
\brief do anything needed prior to arrival of audio buffers

Operation:
- updateOutBoundVariables sends metering data to the GUI meters

\param processInfo structure of information about *buffer* processing

\return true if operation succeeds, false otherwise
*/
bool PluginCore::postProcessAudioBuffers(ProcessBufferInfo& processInfo)
{
	// --- update outbound variables; currently this is meter data only, but could be extended
	//     in the future
	updateOutBoundVariables();

    return true;
}

/**
\brief update the PluginParameter's value based on GUI control, preset, or data smoothing (thread-safe)

Operation:
- update the parameter's value (with smoothing this initiates another smoothing process)
- call postUpdatePluginParameter to do any further processing

\param controlID the control ID value of the parameter being updated
\param controlValue the new control value
\param paramInfo structure of information about why this value is being udpated (e.g as a result of a preset being loaded vs. the top of a buffer process cycle)

\return true if operation succeeds, false otherwise
*/
bool PluginCore::updatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo)
{
    // --- use base class helper
    setPIParamValue(controlID, controlValue);

    // --- do any post-processing
    postUpdatePluginParameter(controlID, controlValue, paramInfo);

    return true; /// handled
}




/**
\brief update the PluginParameter's value based on *normlaized* GUI control, preset, or data smoothing (thread-safe)

Operation:
- update the parameter's value (with smoothing this initiates another smoothing process)
- call postUpdatePluginParameter to do any further processing

\param controlID the control ID value of the parameter being updated
\param normalizedValue the new control value in normalized form
\param paramInfo structure of information about why this value is being udpated (e.g as a result of a preset being loaded vs. the top of a buffer process cycle)

\return true if operation succeeds, false otherwise
*/
bool PluginCore::updatePluginParameterNormalized(int32_t controlID, double normalizedValue, ParameterUpdateInfo& paramInfo)
{
	// --- use base class helper, returns actual value
	double controlValue = setPIParamValueNormalized(controlID, normalizedValue, paramInfo.applyTaper);

	// --- do any post-processing
	postUpdatePluginParameter(controlID, controlValue, paramInfo);

	return true; /// handled
}

/**
\brief perform any operations after the plugin parameter has been updated; this is one paradigm for
	   transferring control information into vital plugin variables or member objects. If you use this
	   method you can decode the control ID and then do any cooking that is needed. NOTE: do not
	   overwrite bound variables here - this is ONLY for any extra cooking that is required to convert
	   the GUI data to meaninful coefficients or other specific modifiers.

\param controlID the control ID value of the parameter being updated
\param controlValue the new control value
\param paramInfo structure of information about why this value is being udpated (e.g as a result of a preset being loaded vs. the top of a buffer process cycle)

\return true if operation succeeds, false otherwise
*/
bool PluginCore::postUpdatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo)
{
    // --- now do any post update cooking; be careful with VST Sample Accurate automation
    //     If enabled, then make sure the cooking functions are short and efficient otherwise disable it
    //     for the Parameter involved
    /*switch(controlID)
    {
        case 0:
        {
            return true;    /// handled
        }

        default:
            return false;   /// not handled
    }*/

    return false;
}

/**
\brief has nothing to do with actual variable or updated variable (binding)

CAUTION:
- DO NOT update underlying variables here - this is only for sending GUI updates or letting you
  know that a parameter was changed; it should not change the state of your plugin.

WARNING:
- THIS IS NOT THE PREFERRED WAY TO LINK OR COMBINE CONTROLS TOGETHER. THE PROPER METHOD IS
  TO USE A CUSTOM SUB-CONTROLLER THAT IS PART OF THE GUI OBJECT AND CODE.
  SEE http://www.willpirkle.com for more information

\param controlID the control ID value of the parameter being updated
\param actualValue the new control value

\return true if operation succeeds, false otherwise
*/
bool PluginCore::guiParameterChanged(int32_t controlID, double actualValue)
{

	//EQ presets part ----------------------------------------------------------------------

	//host message for GUI update
	HostMessageInfo hostMessageInfo;
	hostMessageInfo.hostMessage = sendGUIUpdate;
	
	//1
	GUIParameter boostCut1Param;
	boostCut1Param.controlID = controlID::boostCut1;
	//2
	GUIParameter boostCut2Param;
	boostCut2Param.controlID = controlID::boostCut2;
	//3
	GUIParameter boostCut3Param;
	boostCut3Param.controlID = controlID::boostCut3;
	//4
	GUIParameter boostCut4Param;
	boostCut4Param.controlID = controlID::boostCut4;
	//5
	GUIParameter boostCut5Param;
	boostCut5Param.controlID = controlID::boostCut5;
	//6
	GUIParameter boostCut6Param;
	boostCut6Param.controlID = controlID::boostCut6;
	//7
	GUIParameter boostCut7Param;
	boostCut7Param.controlID = controlID::boostCut7;
	//8
	GUIParameter boostCut8Param;
	boostCut8Param.controlID = controlID::boostCut8;
	//9
	GUIParameter boostCut9Param;
	boostCut9Param.controlID = controlID::boostCut9;
	//10
	GUIParameter boostCut10Param;
	boostCut10Param.controlID = controlID::boostCut10;

	//X
	GUIParameter xCoordParam;
	xCoordParam.controlID = controlID::xCoord;
	//X
	GUIParameter yCoordParam;
	yCoordParam.controlID = controlID::yCoord;

	//EQ presets
	GUIParameter eqPresetParam;
	eqPresetParam.controlID = controlID::eqPreset;

	switch (controlID)
	{
	case controlID::eqPreset:
		{

		//Cassica --------------------------------------------------------------------------
		if (actualValue == 0.0){

			//non custom
			isCustom = false;
			xCoordParam.actualValue = 50.000000;
			yCoordParam.actualValue = 0.000000;
			//manipolo parametri
			
			boostCut1Param.actualValue = 0;			
			boostCut2Param.actualValue = 0;			
			boostCut3Param.actualValue = 0;			
			boostCut4Param.actualValue = 0;			
			boostCut5Param.actualValue = 0;			
			boostCut6Param.actualValue = 0;			
			boostCut7Param.actualValue = -7.2;			
			boostCut8Param.actualValue = -7.2;			
			boostCut9Param.actualValue = -7.2;				
			boostCut10Param.actualValue = -9.6;			
			
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut1Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut2Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut3Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut4Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut5Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut6Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut7Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut8Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut9Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut10Param);

			hostMessageInfo.guiUpdateData.guiParameters.push_back(xCoordParam);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(yCoordParam);
			pluginHostConnector->sendHostMessage(hostMessageInfo);

			//volume = 12;

			/*boostCut1 = 0;
			boostCut2 = 0;
			boostCut3 = 0;
			boostCut4 = 0;
			boostCut5 = 0;
			boostCut6 = -7.2;
			boostCut7 = -7.2;
			boostCut8 = -7.2;
			boostCut9 = -7.2;*/
			//boostCut10 = -9.6;
		}

		//Dance --------------------------------------------------------------------------
		if (actualValue == 1.0) {

			//non custom
			isCustom = false;
			xCoordParam.actualValue = 50.000000;
			yCoordParam.actualValue = 0.000000;
			//manipolo parametri

			boostCut1Param.actualValue = 9.6;
			boostCut2Param.actualValue = 7.2;
			boostCut3Param.actualValue = 2.4;
			boostCut4Param.actualValue = 0;
			boostCut5Param.actualValue = 0;
			boostCut6Param.actualValue = -5.6;
			boostCut7Param.actualValue = -7.2;
			boostCut8Param.actualValue = -7.2;
			boostCut9Param.actualValue = 0;
			boostCut10Param.actualValue = 0;

			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut1Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut2Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut3Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut4Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut5Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut6Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut7Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut8Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut9Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut10Param);

			hostMessageInfo.guiUpdateData.guiParameters.push_back(xCoordParam);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(yCoordParam);
			pluginHostConnector->sendHostMessage(hostMessageInfo);

			
		}

		//Pop --------------------------------------------------------------------------
		if (actualValue == 2.0) {

			//non custom
			isCustom = false;
			xCoordParam.actualValue = 50.000000;
			yCoordParam.actualValue = 0.000000;
			//manipolo parametri

			boostCut1Param.actualValue = -1.6;
			boostCut2Param.actualValue = 4.8;
			boostCut3Param.actualValue = 7.2;
			boostCut4Param.actualValue = 8;
			boostCut5Param.actualValue = 5.6;
			boostCut6Param.actualValue = 0;
			boostCut7Param.actualValue = -2.4;
			boostCut8Param.actualValue = -2.4;
			boostCut9Param.actualValue = -1.6;
			boostCut10Param.actualValue = -1.6;

			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut1Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut2Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut3Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut4Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut5Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut6Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut7Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut8Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut9Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut10Param);

			hostMessageInfo.guiUpdateData.guiParameters.push_back(xCoordParam);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(yCoordParam);
			pluginHostConnector->sendHostMessage(hostMessageInfo);

		}

		//Reggae --------------------------------------------------------------------------
		if (actualValue == 3.0) {

			//non custom
			isCustom = false;
			xCoordParam.actualValue = 50.000000;
			yCoordParam.actualValue = 0.000000;
			//manipolo parametri

			boostCut1Param.actualValue = 0;
			boostCut2Param.actualValue = 0;
			boostCut3Param.actualValue = 0;
			boostCut4Param.actualValue = -5.6;
			boostCut5Param.actualValue = 0;
			boostCut6Param.actualValue = 6.1;
			boostCut7Param.actualValue = 6.1;
			boostCut8Param.actualValue = 0;
			boostCut9Param.actualValue = 0;
			boostCut10Param.actualValue = 0;

			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut1Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut2Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut3Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut4Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut5Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut6Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut7Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut8Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut9Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut10Param);

			hostMessageInfo.guiUpdateData.guiParameters.push_back(xCoordParam);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(yCoordParam);
			pluginHostConnector->sendHostMessage(hostMessageInfo);

		}

		//Rock --------------------------------------------------------------------------
		if (actualValue == 4.0) {

			//non custom
			isCustom = false;
			xCoordParam.actualValue = 50.000000;
			yCoordParam.actualValue = 0.000000;

			//manipolo parametri

			boostCut1Param.actualValue = 8;
			boostCut2Param.actualValue = 4.8;
			boostCut3Param.actualValue = -5.6;
			boostCut4Param.actualValue = -8;
			boostCut5Param.actualValue = -3.2;
			boostCut6Param.actualValue = 4;
			boostCut7Param.actualValue = 8.8;
			boostCut8Param.actualValue = 11.2;
			boostCut9Param.actualValue = 11.2;
			boostCut10Param.actualValue = 11.2;

			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut1Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut2Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut3Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut4Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut5Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut6Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut7Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut8Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut9Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut10Param);

			hostMessageInfo.guiUpdateData.guiParameters.push_back(xCoordParam);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(yCoordParam);
			pluginHostConnector->sendHostMessage(hostMessageInfo);

		}

		//Metal ---------------------- DA VALORIZZARE --------------------------------------------------------------------------
		if (actualValue == 5.0) {

			//non custom
			isCustom = false;
			xCoordParam.actualValue = 50.000000;
			yCoordParam.actualValue = 0.000000;

			//manipolo parametri

			boostCut1Param.actualValue = 10;
			boostCut2Param.actualValue = 8.3;
			boostCut3Param.actualValue = 0.5;
			boostCut4Param.actualValue = 5;
			boostCut5Param.actualValue = 0.2;
			boostCut6Param.actualValue = 0.2;
			boostCut7Param.actualValue = 6;
			boostCut8Param.actualValue = 2;
			boostCut9Param.actualValue = 9;
			boostCut10Param.actualValue = 10;

			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut1Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut2Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut3Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut4Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut5Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut6Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut7Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut8Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut9Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut10Param);

			hostMessageInfo.guiUpdateData.guiParameters.push_back(xCoordParam);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(yCoordParam);
			pluginHostConnector->sendHostMessage(hostMessageInfo);

		}

		//Club --------------------------------------------------------------------------
		if (actualValue == 6.0) {

			//non custom
			isCustom = false;
			xCoordParam.actualValue = 50.000000;
			yCoordParam.actualValue = 0.000000;
			//manipolo parametri

			boostCut1Param.actualValue = 0;
			boostCut2Param.actualValue = 0;
			boostCut3Param.actualValue = 8;
			boostCut4Param.actualValue = 5.6;
			boostCut5Param.actualValue = 5.6;
			boostCut6Param.actualValue = 5.6;
			boostCut7Param.actualValue = 3.2;
			boostCut8Param.actualValue = 0;
			boostCut9Param.actualValue = 0;
			boostCut10Param.actualValue = 0;

			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut1Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut2Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut3Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut4Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut5Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut6Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut7Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut8Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut9Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut10Param);

			hostMessageInfo.guiUpdateData.guiParameters.push_back(xCoordParam);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(yCoordParam);
			pluginHostConnector->sendHostMessage(hostMessageInfo);

		}

		//Party --------------------------------------------------------------------------
		if (actualValue == 7.0) {

			//non custom
			isCustom = false;
			xCoordParam.actualValue = 50.000000;
			yCoordParam.actualValue = 0.000000;
			//manipolo parametri
			 //boostCut1_prev = 7.2;
			boostCut1Param.actualValue = 7.2;
			boostCut2Param.actualValue = 7.2;
			boostCut3Param.actualValue = 8;
			boostCut4Param.actualValue = 5.6;
			boostCut5Param.actualValue = 5.6;
			boostCut6Param.actualValue = 5.6;
			boostCut7Param.actualValue = 3.2;
			boostCut8Param.actualValue = 0;
			boostCut9Param.actualValue = 7.2;
			boostCut10Param.actualValue = 7.2;

			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut1Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut2Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut3Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut4Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut5Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut6Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut7Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut8Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut9Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut10Param);

			hostMessageInfo.guiUpdateData.guiParameters.push_back(xCoordParam);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(yCoordParam);
			pluginHostConnector->sendHostMessage(hostMessageInfo);

		}

		//Flat --------------------------------------------------------------------------
		if (actualValue == 8.0) {

			//non custom
			isCustom = false;
			xCoordParam.actualValue = 50.000000;
			yCoordParam.actualValue = 0.000000;
			//manipolo parametri

			boostCut1Param.actualValue = 0;
			boostCut2Param.actualValue = 0;
			boostCut3Param.actualValue = 0;
			boostCut4Param.actualValue = 0;
			boostCut5Param.actualValue = 0;
			boostCut6Param.actualValue = 0;
			boostCut7Param.actualValue = 0;
			boostCut8Param.actualValue = 0;
			boostCut9Param.actualValue = 0;
			boostCut10Param.actualValue = 0;

			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut1Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut2Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut3Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut4Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut5Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut6Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut7Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut8Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut9Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut10Param);

			hostMessageInfo.guiUpdateData.guiParameters.push_back(xCoordParam);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(yCoordParam);

			pluginHostConnector->sendHostMessage(hostMessageInfo);

		}

		//Custom --------------------------------------------------------------------------
		if (actualValue == 9.0) {

			isCustom = true;


			
			
		}

			return true; // handled
		}

		case controlID::xCoord:
		{  
			xActual = actualValue;

			eqPresetParam.actualValue = 9.0;

			isCustom = true;		

			fuzzyEQUpdate(xActual, yActual);
			fuzzyEQUpdate2(xActual, yActual);
			fuzzyEQUpdate3(xActual, yActual);
			fuzzyEQUpdate4(xActual, yActual);
			fuzzyEQUpdate5(xActual, yActual);
			fuzzyEQUpdate6(xActual, yActual);
			fuzzyEQUpdate7(xActual, yActual);
			fuzzyEQUpdate8(xActual, yActual);
			fuzzyEQUpdate9(xActual, yActual);
			fuzzyEQUpdate10(xActual, yActual);

			/*
			if(xActual + yActual <= 20.00f)
				boostCut1Param.actualValue = (double) xActual + yActual;
			else
				boostCut1Param.actualValue = 0;
			*/

			//Aggiorno le frequenze secondo le regole fuzzy (x) e la percentuale (y)
			
			boostCut1Param.actualValue = (double) f1Fuzzy + (double) f1Fuzzy * yActual/100;
			boostCut2Param.actualValue = (double) f2Fuzzy + (double) f2Fuzzy * yActual / 100;
			boostCut3Param.actualValue = (double) f3Fuzzy + (double) f3Fuzzy * yActual / 100;
			boostCut4Param.actualValue = (double) f4Fuzzy + (double) f4Fuzzy * yActual / 100;
			boostCut5Param.actualValue = (double) f5Fuzzy + (double) f5Fuzzy * yActual / 100;
			boostCut6Param.actualValue = (double) f6Fuzzy + (double) f6Fuzzy * yActual / 100;
			boostCut7Param.actualValue = (double) f7Fuzzy + (double) f7Fuzzy * yActual / 100;
			boostCut8Param.actualValue = (double) f8Fuzzy + (double) f8Fuzzy * yActual / 100;
			boostCut9Param.actualValue = (double) f9Fuzzy + (double) f9Fuzzy * yActual / 100;
			boostCut10Param.actualValue = (double) f10Fuzzy + (double) f10Fuzzy * yActual / 100;
			
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut1Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut2Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut3Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut4Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut5Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut6Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut7Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut8Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut9Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut10Param);


			hostMessageInfo.guiUpdateData.guiParameters.push_back(eqPresetParam);

			pluginHostConnector->sendHostMessage(hostMessageInfo);

			return true; // handled
		}

		case controlID::yCoord:
		{
			yActual = actualValue;

			eqPresetParam.actualValue = 9.0;
			
			isCustom = true;

			//Aggiorno le frequenze secondo le regole fuzzy (x) e la percentuale (y)

			boostCut1Param.actualValue = (double)f1Fuzzy + (double)f1Fuzzy * yActual / 100;
			boostCut2Param.actualValue = (double)f2Fuzzy + (double)f2Fuzzy * yActual / 100;
			boostCut3Param.actualValue = (double)f3Fuzzy + (double)f3Fuzzy * yActual / 100;
			boostCut4Param.actualValue = (double)f4Fuzzy + (double)f4Fuzzy * yActual / 100;
			boostCut5Param.actualValue = (double)f5Fuzzy + (double)f5Fuzzy * yActual / 100;
			boostCut6Param.actualValue = (double)f6Fuzzy + (double)f6Fuzzy * yActual / 100;
			boostCut7Param.actualValue = (double)f7Fuzzy + (double)f7Fuzzy * yActual / 100;
			boostCut8Param.actualValue = (double)f8Fuzzy + (double)f8Fuzzy * yActual / 100;
			boostCut9Param.actualValue = (double)f9Fuzzy + (double)f9Fuzzy * yActual / 100;
			boostCut10Param.actualValue = (double)f10Fuzzy + (double)f10Fuzzy * yActual / 100;

			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut1Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut2Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut3Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut4Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut5Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut6Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut7Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut8Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut9Param);
			hostMessageInfo.guiUpdateData.guiParameters.push_back(boostCut10Param);

			hostMessageInfo.guiUpdateData.guiParameters.push_back(eqPresetParam);

			pluginHostConnector->sendHostMessage(hostMessageInfo);

			return true; // handled
		}

		default:
			break;
	}

	return false; /// not handled
}

/**
\brief For Custom View and Custom Sub-Controller Operations

NOTES:
- this is for advanced users only to implement custom view and custom sub-controllers
- see the SDK for examples of use

\param messageInfo a structure containing information about the incoming message

\return true if operation succeeds, false otherwise
*/
bool PluginCore::processMessage(MessageInfo& messageInfo)
{
	// --- decode message
	switch (messageInfo.message)
	{
		// --- add customization appearance here
	case PLUGINGUI_DIDOPEN:
	{
		return false;
	}

	// --- NULL pointers so that we don't accidentally use them
	case PLUGINGUI_WILLCLOSE:
	{
		return false;
	}

	// --- update view; this will only be called if the GUI is actually open
	case PLUGINGUI_TIMERPING:
	{
		return false;
	}

	// --- register the custom view, grab the ICustomView interface
	case PLUGINGUI_REGISTER_CUSTOMVIEW:
	{

		return false;
	}

	case PLUGINGUI_REGISTER_SUBCONTROLLER:
	case PLUGINGUI_QUERY_HASUSERCUSTOM:
	case PLUGINGUI_USER_CUSTOMOPEN:
	case PLUGINGUI_USER_CUSTOMCLOSE:
	case PLUGINGUI_EXTERNAL_SET_NORMVALUE:
	case PLUGINGUI_EXTERNAL_SET_ACTUALVALUE:
	{

		return false;
	}

	default:
		break;
	}

	return false; /// not handled
}


/**
\brief process a MIDI event

NOTES:
- MIDI events are 100% sample accurate; this function will be called repeatedly for every MIDI message
- see the SDK for examples of use

\param event a structure containing the MIDI event data

\return true if operation succeeds, false otherwise
*/
bool PluginCore::processMIDIEvent(midiEvent& event)
{
	return true;
}

/**
\brief (for future use)

NOTES:
- MIDI events are 100% sample accurate; this function will be called repeatedly for every MIDI message
- see the SDK for examples of use

\param vectorJoysickData a structure containing joystick data

\return true if operation succeeds, false otherwise
*/
bool PluginCore::setVectorJoystickParameters(const VectorJoystickData& vectorJoysickData)
{
	return true;
}

/**
\brief use this method to add new presets to the list

NOTES:
- see the SDK for examples of use
- for non RackAFX users that have large paramter counts, there is a secret GUI control you
  can enable to write C++ code into text files, one per preset. See the SDK or http://www.willpirkle.com for details

\return true if operation succeeds, false otherwise
*/
bool PluginCore::initPluginPresets()
{
	// **--0xFF7A--**

	// --- Plugin Presets 
	int index = 0;
	PresetInfo* preset = nullptr;

	// --- Preset: Factory Preset
	preset = new PresetInfo(index++, "Factory Preset");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::volume, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::boostCut, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::boostCut1, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::boostCut2, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::boostCut3, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::boostCut4, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::boostCut5, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::boostCut6, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::boostCut7, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::boostCut8, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::boostCut9, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::boostCut10, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::eqPreset, 8.000000);
	setPresetParameter(preset->presetParameters, controlID::xCoord, 50.000000);
	setPresetParameter(preset->presetParameters, controlID::yCoord, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::fuzzyLed, 1.000000);
	addPreset(preset);


	// **--0xA7FF--**

    return true;
}

void PluginCore::fuzzyEQUpdate(double x, double y)
{
	//Motore per F1 ***********************************************************************************************************
	Engine* engine = new Engine;
	engine->setName("FuzzyTouchPad");
	engine->setDescription("Motore Fuzzy GEQ");
	//Input tipo suono 
	//Input x
	InputVariable* xFuzzyCoord = new InputVariable;
	xFuzzyCoord->setName("x");
	//xFuzzyCoord->setValue(x);
	xFuzzyCoord->setDescription("");
	xFuzzyCoord->setEnabled(true);
	xFuzzyCoord->setRange(0.000, 100.000);
	xFuzzyCoord->setLockValueInRange(false);
	
	xFuzzyCoord->addTerm(new Triangle("profondo", 0.000, 0.000, 11.111));
	xFuzzyCoord->addTerm(new Triangle("avvolgente", 0.000, 11.111, 22.222));
	xFuzzyCoord->addTerm(new Triangle("morbido", 11.111, 22.222, 33.333));
	xFuzzyCoord->addTerm(new Triangle("largo", 22.222, 33.333, 44.444));
	xFuzzyCoord->addTerm(new Triangle("ampio", 33.333, 44.444, 55.555));
	xFuzzyCoord->addTerm(new Triangle("arioso", 44.444, 55.555, 66.666));
	xFuzzyCoord->addTerm(new Triangle("fresco", 55.555, 66.666, 77.777));
	xFuzzyCoord->addTerm(new Triangle("gelido", 66.666, 77.777, 88.888));
	xFuzzyCoord->addTerm(new Triangle("polare", 77.777, 88.888, 100.100));

	engine->addInputVariable(xFuzzyCoord);

	//output 
	OutputVariable* fuzzyBoostCut1 = new OutputVariable;
	fuzzyBoostCut1->setName("fuzzyBoostCut1");
	fuzzyBoostCut1->setDescription("Mamdani inference");
	fuzzyBoostCut1->setEnabled(true);
	fuzzyBoostCut1->setRange(-20.000, 20.000);
	fuzzyBoostCut1->setLockValueInRange(false);
	fuzzyBoostCut1->setAggregation(new Maximum);
	fuzzyBoostCut1->setDefuzzifier(new Centroid(100));
	fuzzyBoostCut1->setDefaultValue(0.000);//provare -> fl::nan
	fuzzyBoostCut1->setLockPreviousValue(false);

	fuzzyBoostCut1->addTerm(new Triangle("attenua_tanto", -20.000, -20.000, -10.000));
	fuzzyBoostCut1->addTerm(new Triangle("attenua", -15.000, -10.000, -5.000));
	fuzzyBoostCut1->addTerm(new Triangle("attenua_poco", -10.000, -5.000, 0.000));
	fuzzyBoostCut1->addTerm(new Triangle("neutro", -5.000, 0.000, 5.000));
	fuzzyBoostCut1->addTerm(new Triangle("incrementa_poco", 0.000, 5.000, 10.000));
	fuzzyBoostCut1->addTerm(new Triangle("incrementa", 5.000, 10.000, 15.000));
	fuzzyBoostCut1->addTerm(new Triangle("incrementa_tanto", 10.000, 15.000, 20.000));

	engine->addOutputVariable(fuzzyBoostCut1);

	//Fuzzy rules
	RuleBlock* mamdani = new RuleBlock;
	mamdani->setName("mamdani");
	mamdani->setDescription("");
	mamdani->setEnabled(true);
	mamdani->setConjunction(new AlgebraicProduct);
	mamdani->setDisjunction(new AlgebraicSum);
	mamdani->setImplication(new Minimum);
	mamdani->setActivation(new General);

	mamdani->addRule(Rule::parse("if x is profondo then fuzzyBoostCut1 is incrementa_tanto", engine));
	mamdani->addRule(Rule::parse("if x is avvolgente then fuzzyBoostCut1 is incrementa", engine));
	mamdani->addRule(Rule::parse("if x is morbido then fuzzyBoostCut1 is incrementa_poco", engine));
	mamdani->addRule(Rule::parse("if x is largo then fuzzyBoostCut1 is neutro", engine));
	mamdani->addRule(Rule::parse("if x is ampio  then fuzzyBoostCut1 is neutro", engine));
	mamdani->addRule(Rule::parse("if x is arioso then fuzzyBoostCut1 is attenua_poco", engine));
	mamdani->addRule(Rule::parse("if x is fresco then fuzzyBoostCut1 is attenua", engine));
	mamdani->addRule(Rule::parse("if x is gelido  then fuzzyBoostCut1 is attenua_tanto", engine));
	mamdani->addRule(Rule::parse("if x is polare then fuzzyBoostCut1 is attenua_tanto", engine));

	mamdani->activate();
	engine->addRuleBlock(mamdani);	

	xFuzzyCoord->setValue(x);
	
	engine->process();	

	f1Fuzzy = fuzzyBoostCut1->getValue();
	// FINE Motore per F1 ***********************************************************************************************************

}

void PluginCore::fuzzyEQUpdate2(double x, double y)
{
	//Motore per F2 ***********************************************************************************************************	
	Engine* engine = new Engine;
	engine->setName("FuzzyTouchPad");
	engine->setDescription("Motore Fuzzy GEQ");
	//Input tipo suono 
	//Input x
	InputVariable* xFuzzyCoord = new InputVariable;
	xFuzzyCoord->setName("x");
	xFuzzyCoord->setDescription("");
	xFuzzyCoord->setEnabled(true);
	xFuzzyCoord->setRange(0.000, 100.000);
	xFuzzyCoord->setLockValueInRange(false);

	xFuzzyCoord->addTerm(new Triangle("profondo", 0.000, 0.000, 11.111));
	xFuzzyCoord->addTerm(new Triangle("avvolgente", 0.000, 11.111, 22.222));
	xFuzzyCoord->addTerm(new Triangle("morbido", 11.111, 22.222, 33.333));
	xFuzzyCoord->addTerm(new Triangle("largo", 22.222, 33.333, 44.444));
	xFuzzyCoord->addTerm(new Triangle("ampio", 33.333, 44.444, 55.555));
	xFuzzyCoord->addTerm(new Triangle("arioso", 44.444, 55.555, 66.666));
	xFuzzyCoord->addTerm(new Triangle("fresco", 55.555, 66.666, 77.777));
	xFuzzyCoord->addTerm(new Triangle("gelido", 66.666, 77.777, 88.888));
	xFuzzyCoord->addTerm(new Triangle("polare", 77.777, 88.888, 100.100));

	engine->addInputVariable(xFuzzyCoord);

	//output 
	OutputVariable* fuzzyBoostCut = new OutputVariable;
	fuzzyBoostCut->setName("fuzzyBoostCut");
	fuzzyBoostCut->setDescription("Mamdani inference");
	fuzzyBoostCut->setEnabled(true);
	fuzzyBoostCut->setRange(-20.000, 20.000);
	fuzzyBoostCut->setLockValueInRange(false);
	fuzzyBoostCut->setAggregation(new Maximum);
	fuzzyBoostCut->setDefuzzifier(new Centroid(100));
	fuzzyBoostCut->setDefaultValue(0.000);//provare -> fl::nan
	fuzzyBoostCut->setLockPreviousValue(false);
	fuzzyBoostCut->addTerm(new Triangle("attenua_tanto", -20.000, -20.000, -10.000));
	fuzzyBoostCut->addTerm(new Triangle("attenua", -15.000, -10.000, -5.000));
	fuzzyBoostCut->addTerm(new Triangle("attenua_poco", -10.000, -5.000, 0.000));
	fuzzyBoostCut->addTerm(new Triangle("neutro", -5.000, 0.000, 5.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa_poco", 0.000, 5.000, 10.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa", 5.000, 10.000, 15.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa_tanto", 10.000, 15.000, 20.000));

	engine->addOutputVariable(fuzzyBoostCut);

	//Fuzzy rules
	RuleBlock* mamdani = new RuleBlock;
	mamdani->setName("mamdani");
	mamdani->setDescription("");
	mamdani->setEnabled(true);
	mamdani->setConjunction(new AlgebraicProduct);
	mamdani->setDisjunction(new AlgebraicSum);
	mamdani->setImplication(new Minimum);
	mamdani->setActivation(new General);

	mamdani->addRule(Rule::parse("if x is profondo then fuzzyBoostCut is incrementa", engine));
	mamdani->addRule(Rule::parse("if x is avvolgente  then fuzzyBoostCut is incrementa", engine));
	mamdani->addRule(Rule::parse("if x is morbido then fuzzyBoostCut is incrementa_poco", engine));
	mamdani->addRule(Rule::parse("if x is largo then fuzzyBoostCut is neutro", engine));
	mamdani->addRule(Rule::parse("if x is ampio  then fuzzyBoostCut is neutro", engine));
	mamdani->addRule(Rule::parse("if x is arioso then fuzzyBoostCut is attenua_poco", engine));
	mamdani->addRule(Rule::parse("if x is fresco then fuzzyBoostCut is attenua", engine));
	mamdani->addRule(Rule::parse("if x is gelido  then fuzzyBoostCut is attenua", engine));
	mamdani->addRule(Rule::parse("if x is polare then fuzzyBoostCut is attenua_tanto", engine));

	mamdani->activate();
	engine->addRuleBlock(mamdani);

	xFuzzyCoord->setValue(x);

	engine->process();

	f2Fuzzy = fuzzyBoostCut->getValue();

	// FINE Motore per F2 ***********************************************************************************************************

}

void PluginCore::fuzzyEQUpdate3(double x, double y)
{
	//Motore per F3 ***********************************************************************************************************	
	Engine* engine = new Engine;
	engine->setName("FuzzyTouchPad");
	engine->setDescription("Motore Fuzzy GEQ");
	//Input tipo suono 
	//Input x
	InputVariable* xFuzzyCoord = new InputVariable;
	xFuzzyCoord->setName("x");
	xFuzzyCoord->setDescription("");
	xFuzzyCoord->setEnabled(true);
	xFuzzyCoord->setRange(0.000, 100.000);
	xFuzzyCoord->setLockValueInRange(false);

	xFuzzyCoord->addTerm(new Triangle("profondo", 0.000, 0.000, 11.111));
	xFuzzyCoord->addTerm(new Triangle("avvolgente", 0.000, 11.111, 22.222));
	xFuzzyCoord->addTerm(new Triangle("morbido", 11.111, 22.222, 33.333));
	xFuzzyCoord->addTerm(new Triangle("largo", 22.222, 33.333, 44.444));
	xFuzzyCoord->addTerm(new Triangle("ampio", 33.333, 44.444, 55.555));
	xFuzzyCoord->addTerm(new Triangle("arioso", 44.444, 55.555, 66.666));
	xFuzzyCoord->addTerm(new Triangle("fresco", 55.555, 66.666, 77.777));
	xFuzzyCoord->addTerm(new Triangle("gelido", 66.666, 77.777, 88.888));
	xFuzzyCoord->addTerm(new Triangle("polare", 77.777, 88.888, 100.100));

	engine->addInputVariable(xFuzzyCoord);

	//output 
	OutputVariable* fuzzyBoostCut = new OutputVariable;
	fuzzyBoostCut->setName("fuzzyBoostCut");
	fuzzyBoostCut->setDescription("Mamdani inference");
	fuzzyBoostCut->setEnabled(true);
	fuzzyBoostCut->setRange(-20.000, 20.000);
	fuzzyBoostCut->setLockValueInRange(false);
	fuzzyBoostCut->setAggregation(new Maximum);
	fuzzyBoostCut->setDefuzzifier(new Centroid(100));
	fuzzyBoostCut->setDefaultValue(0.000);//provare -> fl::nan
	fuzzyBoostCut->setLockPreviousValue(false);
	fuzzyBoostCut->addTerm(new Triangle("attenua_tanto", -20.000, -20.000, -10.000));
	fuzzyBoostCut->addTerm(new Triangle("attenua", -15.000, -10.000, -5.000));
	fuzzyBoostCut->addTerm(new Triangle("attenua_poco", -10.000, -5.000, 0.000));
	fuzzyBoostCut->addTerm(new Triangle("neutro", -5.000, 0.000, 5.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa_poco", 0.000, 5.000, 10.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa", 5.000, 10.000, 15.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa_tanto", 10.000, 15.000, 20.000));

	engine->addOutputVariable(fuzzyBoostCut);

	//Fuzzy rules
	RuleBlock* mamdani = new RuleBlock;
	mamdani->setName("mamdani");
	mamdani->setDescription("");
	mamdani->setEnabled(true);
	mamdani->setConjunction(new AlgebraicProduct);
	mamdani->setDisjunction(new AlgebraicSum);
	mamdani->setImplication(new Minimum);
	mamdani->setActivation(new General);		

	mamdani->addRule(Rule::parse("if x is profondo then fuzzyBoostCut is incrementa", engine));
	mamdani->addRule(Rule::parse("if x is avvolgente  then fuzzyBoostCut is incrementa_poco", engine));
	mamdani->addRule(Rule::parse("if x is morbido then fuzzyBoostCut is incrementa_poco", engine));
	mamdani->addRule(Rule::parse("if x is largo then fuzzyBoostCut is neutro", engine));
	mamdani->addRule(Rule::parse("if x is ampio  then fuzzyBoostCut is neutro", engine));
	mamdani->addRule(Rule::parse("if x is arioso then fuzzyBoostCut is attenua_poco", engine));
	mamdani->addRule(Rule::parse("if x is fresco then fuzzyBoostCut is attenua", engine));
	mamdani->addRule(Rule::parse("if x is gelido  then fuzzyBoostCut is attenua", engine));
	mamdani->addRule(Rule::parse("if x is polare then fuzzyBoostCut is attenua_tanto", engine));

	mamdani->activate();
	engine->addRuleBlock(mamdani);

	xFuzzyCoord->setValue(x);

	engine->process();

	f3Fuzzy = fuzzyBoostCut->getValue();

	// FINE Motore per F3 ***********************************************************************************************************

}

void PluginCore::fuzzyEQUpdate4(double x, double y)
{
	//Motore per F4 ***********************************************************************************************************	
	Engine* engine = new Engine;
	engine->setName("FuzzyTouchPad");
	engine->setDescription("Motore Fuzzy GEQ");
	//Input tipo suono 
	//Input x
	InputVariable* xFuzzyCoord = new InputVariable;
	xFuzzyCoord->setName("x");
	xFuzzyCoord->setDescription("");
	xFuzzyCoord->setEnabled(true);
	xFuzzyCoord->setRange(0.000, 100.000);
	xFuzzyCoord->setLockValueInRange(false);

	xFuzzyCoord->addTerm(new Triangle("profondo", 0.000, 0.000, 11.111));
	xFuzzyCoord->addTerm(new Triangle("avvolgente", 0.000, 11.111, 22.222));
	xFuzzyCoord->addTerm(new Triangle("morbido", 11.111, 22.222, 33.333));
	xFuzzyCoord->addTerm(new Triangle("largo", 22.222, 33.333, 44.444));
	xFuzzyCoord->addTerm(new Triangle("ampio", 33.333, 44.444, 55.555));
	xFuzzyCoord->addTerm(new Triangle("arioso", 44.444, 55.555, 66.666));
	xFuzzyCoord->addTerm(new Triangle("fresco", 55.555, 66.666, 77.777));
	xFuzzyCoord->addTerm(new Triangle("gelido", 66.666, 77.777, 88.888));
	xFuzzyCoord->addTerm(new Triangle("polare", 77.777, 88.888, 100.100));

	engine->addInputVariable(xFuzzyCoord);

	//output 
	OutputVariable* fuzzyBoostCut = new OutputVariable;
	fuzzyBoostCut->setName("fuzzyBoostCut");
	fuzzyBoostCut->setDescription("Mamdani inference");
	fuzzyBoostCut->setEnabled(true);
	fuzzyBoostCut->setRange(-20.000, 20.000);
	fuzzyBoostCut->setLockValueInRange(false);
	fuzzyBoostCut->setAggregation(new Maximum);
	fuzzyBoostCut->setDefuzzifier(new Centroid(100));
	fuzzyBoostCut->setDefaultValue(0.000);//provare -> fl::nan
	fuzzyBoostCut->setLockPreviousValue(false);
	fuzzyBoostCut->addTerm(new Triangle("attenua_tanto", -20.000, -20.000, -10.000));
	fuzzyBoostCut->addTerm(new Triangle("attenua", -15.000, -10.000, -5.000));
	fuzzyBoostCut->addTerm(new Triangle("attenua_poco", -10.000, -5.000, 0.000));
	fuzzyBoostCut->addTerm(new Triangle("neutro", -5.000, 0.000, 5.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa_poco", 0.000, 5.000, 10.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa", 5.000, 10.000, 15.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa_tanto", 10.000, 15.000, 20.000));

	engine->addOutputVariable(fuzzyBoostCut);

	//Fuzzy rules
	RuleBlock* mamdani = new RuleBlock;
	mamdani->setName("mamdani");
	mamdani->setDescription("");
	mamdani->setEnabled(true);
	mamdani->setConjunction(new AlgebraicProduct);
	mamdani->setDisjunction(new AlgebraicSum);
	mamdani->setImplication(new Minimum);
	mamdani->setActivation(new General);

	mamdani->addRule(Rule::parse("if x is profondo then fuzzyBoostCut is incrementa_poco", engine));
	mamdani->addRule(Rule::parse("if x is avvolgente  then fuzzyBoostCut is neutro", engine));
	mamdani->addRule(Rule::parse("if x is morbido then fuzzyBoostCut is neutro", engine));
	mamdani->addRule(Rule::parse("if x is largo then fuzzyBoostCut is neutro", engine));
	mamdani->addRule(Rule::parse("if x is ampio  then fuzzyBoostCut is attenua_poco", engine));
	mamdani->addRule(Rule::parse("if x is arioso then fuzzyBoostCut is attenua_poco", engine));
	mamdani->addRule(Rule::parse("if x is fresco then fuzzyBoostCut is attenua", engine));
	mamdani->addRule(Rule::parse("if x is gelido  then fuzzyBoostCut is attenua", engine));
	mamdani->addRule(Rule::parse("if x is polare then fuzzyBoostCut is attenua", engine));

	mamdani->activate();
	engine->addRuleBlock(mamdani);

	xFuzzyCoord->setValue(x);

	engine->process();

	f4Fuzzy = fuzzyBoostCut->getValue();

	// FINE Motore per F4 ***********************************************************************************************************

}

void PluginCore::fuzzyEQUpdate5(double x, double y)
{
	//Motore per F5 ***********************************************************************************************************	
	Engine* engine = new Engine;
	engine->setName("FuzzyTouchPad");
	engine->setDescription("Motore Fuzzy GEQ");
	//Input tipo suono 
	//Input x
	InputVariable* xFuzzyCoord = new InputVariable;
	xFuzzyCoord->setName("x");
	xFuzzyCoord->setDescription("");
	xFuzzyCoord->setEnabled(true);
	xFuzzyCoord->setRange(0.000, 100.000);
	xFuzzyCoord->setLockValueInRange(false);

	xFuzzyCoord->addTerm(new Triangle("profondo", 0.000, 0.000, 11.111));
	xFuzzyCoord->addTerm(new Triangle("avvolgente", 0.000, 11.111, 22.222));
	xFuzzyCoord->addTerm(new Triangle("morbido", 11.111, 22.222, 33.333));
	xFuzzyCoord->addTerm(new Triangle("largo", 22.222, 33.333, 44.444));
	xFuzzyCoord->addTerm(new Triangle("ampio", 33.333, 44.444, 55.555));
	xFuzzyCoord->addTerm(new Triangle("arioso", 44.444, 55.555, 66.666));
	xFuzzyCoord->addTerm(new Triangle("fresco", 55.555, 66.666, 77.777));
	xFuzzyCoord->addTerm(new Triangle("gelido", 66.666, 77.777, 88.888));
	xFuzzyCoord->addTerm(new Triangle("polare", 77.777, 88.888, 100.100));

	engine->addInputVariable(xFuzzyCoord);

	//output 
	OutputVariable* fuzzyBoostCut = new OutputVariable;
	fuzzyBoostCut->setName("fuzzyBoostCut");
	fuzzyBoostCut->setDescription("Mamdani inference");
	fuzzyBoostCut->setEnabled(true);
	fuzzyBoostCut->setRange(-20.000, 20.000);
	fuzzyBoostCut->setLockValueInRange(false);
	fuzzyBoostCut->setAggregation(new Maximum);
	fuzzyBoostCut->setDefuzzifier(new Centroid(100));
	fuzzyBoostCut->setDefaultValue(0.000);//provare -> fl::nan
	fuzzyBoostCut->setLockPreviousValue(false);
	fuzzyBoostCut->addTerm(new Triangle("attenua_tanto", -20.000, -20.000, -10.000));
	fuzzyBoostCut->addTerm(new Triangle("attenua", -15.000, -10.000, -5.000));
	fuzzyBoostCut->addTerm(new Triangle("attenua_poco", -10.000, -5.000, 0.000));
	fuzzyBoostCut->addTerm(new Triangle("neutro", -5.000, 0.000, 5.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa_poco", 0.000, 5.000, 10.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa", 5.000, 10.000, 15.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa_tanto", 10.000, 15.000, 20.000));

	engine->addOutputVariable(fuzzyBoostCut);

	//Fuzzy rules
	RuleBlock* mamdani = new RuleBlock;
	mamdani->setName("mamdani");
	mamdani->setDescription("");
	mamdani->setEnabled(true);
	mamdani->setConjunction(new AlgebraicProduct);
	mamdani->setDisjunction(new AlgebraicSum);
	mamdani->setImplication(new Minimum);
	mamdani->setActivation(new General);

	mamdani->addRule(Rule::parse("if x is profondo then fuzzyBoostCut is incrementa_poco", engine));
	mamdani->addRule(Rule::parse("if x is avvolgente  then fuzzyBoostCut is neutro", engine));
	mamdani->addRule(Rule::parse("if x is morbido then fuzzyBoostCut is neutro", engine));
	mamdani->addRule(Rule::parse("if x is largo then fuzzyBoostCut is attenua_poco", engine));
	mamdani->addRule(Rule::parse("if x is ampio  then fuzzyBoostCut is attenua_poco", engine));
	mamdani->addRule(Rule::parse("if x is arioso then fuzzyBoostCut is attenua_poco", engine));
	mamdani->addRule(Rule::parse("if x is fresco then fuzzyBoostCut is attenua", engine));
	mamdani->addRule(Rule::parse("if x is gelido  then fuzzyBoostCut is attenua", engine));
	mamdani->addRule(Rule::parse("if x is polare then fuzzyBoostCut is attenua", engine));

	mamdani->activate();
	engine->addRuleBlock(mamdani);

	xFuzzyCoord->setValue(x);

	engine->process();

	f5Fuzzy = fuzzyBoostCut->getValue();

	// FINE Motore per F5 ***********************************************************************************************************

}

void PluginCore::fuzzyEQUpdate6(double x, double y)
{
	//Motore per F6 ***********************************************************************************************************	
	Engine* engine = new Engine;
	engine->setName("FuzzyTouchPad");
	engine->setDescription("Motore Fuzzy GEQ");
	//Input tipo suono 
	//Input x
	InputVariable* xFuzzyCoord = new InputVariable;
	xFuzzyCoord->setName("x");
	xFuzzyCoord->setDescription("");
	xFuzzyCoord->setEnabled(true);
	xFuzzyCoord->setRange(0.000, 100.000);
	xFuzzyCoord->setLockValueInRange(false);

	xFuzzyCoord->addTerm(new Triangle("profondo", 0.000, 0.000, 11.111));
	xFuzzyCoord->addTerm(new Triangle("avvolgente", 0.000, 11.111, 22.222));
	xFuzzyCoord->addTerm(new Triangle("morbido", 11.111, 22.222, 33.333));
	xFuzzyCoord->addTerm(new Triangle("largo", 22.222, 33.333, 44.444));
	xFuzzyCoord->addTerm(new Triangle("ampio", 33.333, 44.444, 55.555));
	xFuzzyCoord->addTerm(new Triangle("arioso", 44.444, 55.555, 66.666));
	xFuzzyCoord->addTerm(new Triangle("fresco", 55.555, 66.666, 77.777));
	xFuzzyCoord->addTerm(new Triangle("gelido", 66.666, 77.777, 88.888));
	xFuzzyCoord->addTerm(new Triangle("polare", 77.777, 88.888, 100.100));

	engine->addInputVariable(xFuzzyCoord);

	//output 
	OutputVariable* fuzzyBoostCut = new OutputVariable;
	fuzzyBoostCut->setName("fuzzyBoostCut");
	fuzzyBoostCut->setDescription("Mamdani inference");
	fuzzyBoostCut->setEnabled(true);
	fuzzyBoostCut->setRange(-20.000, 20.000);
	fuzzyBoostCut->setLockValueInRange(false);
	fuzzyBoostCut->setAggregation(new Maximum);
	fuzzyBoostCut->setDefuzzifier(new Centroid(100));
	fuzzyBoostCut->setDefaultValue(0.000);//provare -> fl::nan
	fuzzyBoostCut->setLockPreviousValue(false);
	fuzzyBoostCut->addTerm(new Triangle("attenua_tanto", -20.000, -20.000, -10.000));
	fuzzyBoostCut->addTerm(new Triangle("attenua", -15.000, -10.000, -5.000));
	fuzzyBoostCut->addTerm(new Triangle("attenua_poco", -10.000, -5.000, 0.000));
	fuzzyBoostCut->addTerm(new Triangle("neutro", -5.000, 0.000, 5.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa_poco", 0.000, 5.000, 10.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa", 5.000, 10.000, 15.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa_tanto", 10.000, 15.000, 20.000));

	engine->addOutputVariable(fuzzyBoostCut);

	//Fuzzy rules
	RuleBlock* mamdani = new RuleBlock;
	mamdani->setName("mamdani");
	mamdani->setDescription("");
	mamdani->setEnabled(true);
	mamdani->setConjunction(new AlgebraicProduct);
	mamdani->setDisjunction(new AlgebraicSum);
	mamdani->setImplication(new Minimum);
	mamdani->setActivation(new General);

	mamdani->addRule(Rule::parse("if x is profondo then fuzzyBoostCut is attenua", engine));
	mamdani->addRule(Rule::parse("if x is avvolgente  then fuzzyBoostCut is attenua_poco", engine));
	mamdani->addRule(Rule::parse("if x is morbido then fuzzyBoostCut is attenua_poco", engine));
	mamdani->addRule(Rule::parse("if x is largo then fuzzyBoostCut is neutro", engine));
	mamdani->addRule(Rule::parse("if x is ampio  then fuzzyBoostCut is neutro", engine));
	mamdani->addRule(Rule::parse("if x is arioso then fuzzyBoostCut is incrementa_poco", engine));
	mamdani->addRule(Rule::parse("if x is fresco then fuzzyBoostCut is incrementa_poco", engine));
	mamdani->addRule(Rule::parse("if x is gelido  then fuzzyBoostCut is incrementa_poco", engine));
	mamdani->addRule(Rule::parse("if x is polare then fuzzyBoostCut is incrementa_poco", engine));

	mamdani->activate();
	engine->addRuleBlock(mamdani);

	xFuzzyCoord->setValue(x);

	engine->process();

	f6Fuzzy = fuzzyBoostCut->getValue();

	// FINE Motore per F6 ***********************************************************************************************************

}

void PluginCore::fuzzyEQUpdate7(double x, double y)
{
	//Motore per F7 ***********************************************************************************************************	
	Engine* engine = new Engine;
	engine->setName("FuzzyTouchPad");
	engine->setDescription("Motore Fuzzy GEQ");
	//Input tipo suono 
	//Input x
	InputVariable* xFuzzyCoord = new InputVariable;
	xFuzzyCoord->setName("x");
	xFuzzyCoord->setDescription("");
	xFuzzyCoord->setEnabled(true);
	xFuzzyCoord->setRange(0.000, 100.000);
	xFuzzyCoord->setLockValueInRange(false);

	xFuzzyCoord->addTerm(new Triangle("profondo", 0.000, 0.000, 11.111));
	xFuzzyCoord->addTerm(new Triangle("avvolgente", 0.000, 11.111, 22.222));
	xFuzzyCoord->addTerm(new Triangle("morbido", 11.111, 22.222, 33.333));
	xFuzzyCoord->addTerm(new Triangle("largo", 22.222, 33.333, 44.444));
	xFuzzyCoord->addTerm(new Triangle("ampio", 33.333, 44.444, 55.555));
	xFuzzyCoord->addTerm(new Triangle("arioso", 44.444, 55.555, 66.666));
	xFuzzyCoord->addTerm(new Triangle("fresco", 55.555, 66.666, 77.777));
	xFuzzyCoord->addTerm(new Triangle("gelido", 66.666, 77.777, 88.888));
	xFuzzyCoord->addTerm(new Triangle("polare", 77.777, 88.888, 100.100));

	engine->addInputVariable(xFuzzyCoord);

	//output 
	OutputVariable* fuzzyBoostCut = new OutputVariable;
	fuzzyBoostCut->setName("fuzzyBoostCut");
	fuzzyBoostCut->setDescription("Mamdani inference");
	fuzzyBoostCut->setEnabled(true);
	fuzzyBoostCut->setRange(-20.000, 20.000);
	fuzzyBoostCut->setLockValueInRange(false);
	fuzzyBoostCut->setAggregation(new Maximum);
	fuzzyBoostCut->setDefuzzifier(new Centroid(100));
	fuzzyBoostCut->setDefaultValue(0.000);//provare -> fl::nan
	fuzzyBoostCut->setLockPreviousValue(false);
	fuzzyBoostCut->addTerm(new Triangle("attenua_tanto", -20.000, -20.000, -10.000));
	fuzzyBoostCut->addTerm(new Triangle("attenua", -15.000, -10.000, -5.000));
	fuzzyBoostCut->addTerm(new Triangle("attenua_poco", -10.000, -5.000, 0.000));
	fuzzyBoostCut->addTerm(new Triangle("neutro", -5.000, 0.000, 5.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa_poco", 0.000, 5.000, 10.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa", 5.000, 10.000, 15.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa_tanto", 10.000, 15.000, 20.000));

	engine->addOutputVariable(fuzzyBoostCut);

	//Fuzzy rules
	RuleBlock* mamdani = new RuleBlock;
	mamdani->setName("mamdani");
	mamdani->setDescription("");
	mamdani->setEnabled(true);
	mamdani->setConjunction(new AlgebraicProduct);
	mamdani->setDisjunction(new AlgebraicSum);
	mamdani->setImplication(new Minimum);
	mamdani->setActivation(new General);

	mamdani->addRule(Rule::parse("if x is profondo then fuzzyBoostCut is attenua_poco", engine));
	mamdani->addRule(Rule::parse("if x is avvolgente  then fuzzyBoostCut is attenua_poco", engine));
	mamdani->addRule(Rule::parse("if x is morbido then fuzzyBoostCut is attenua_poco", engine));
	mamdani->addRule(Rule::parse("if x is largo then fuzzyBoostCut is neutro", engine));
	mamdani->addRule(Rule::parse("if x is ampio  then fuzzyBoostCut is incrementa", engine));
	mamdani->addRule(Rule::parse("if x is arioso then fuzzyBoostCut is incrementa_tanto", engine));
	mamdani->addRule(Rule::parse("if x is fresco then fuzzyBoostCut is incrementa", engine));
	mamdani->addRule(Rule::parse("if x is gelido  then fuzzyBoostCut is incrementa_poco", engine));
	mamdani->addRule(Rule::parse("if x is polare then fuzzyBoostCut is neutro", engine));

	mamdani->activate();
	engine->addRuleBlock(mamdani);

	xFuzzyCoord->setValue(x);

	engine->process();

	f7Fuzzy = fuzzyBoostCut->getValue();

	// FINE Motore per F7 ***********************************************************************************************************

}

void PluginCore::fuzzyEQUpdate8(double x, double y)
{
	//Motore per F8 ***********************************************************************************************************	
	Engine* engine = new Engine;
	engine->setName("FuzzyTouchPad");
	engine->setDescription("Motore Fuzzy GEQ");
	//Input tipo suono 
	//Input x
	InputVariable* xFuzzyCoord = new InputVariable;
	xFuzzyCoord->setName("x");
	xFuzzyCoord->setDescription("");
	xFuzzyCoord->setEnabled(true);
	xFuzzyCoord->setRange(0.000, 100.000);
	xFuzzyCoord->setLockValueInRange(false);

	xFuzzyCoord->addTerm(new Triangle("profondo", 0.000, 0.000, 11.111));
	xFuzzyCoord->addTerm(new Triangle("avvolgente", 0.000, 11.111, 22.222));
	xFuzzyCoord->addTerm(new Triangle("morbido", 11.111, 22.222, 33.333));
	xFuzzyCoord->addTerm(new Triangle("largo", 22.222, 33.333, 44.444));
	xFuzzyCoord->addTerm(new Triangle("ampio", 33.333, 44.444, 55.555));
	xFuzzyCoord->addTerm(new Triangle("arioso", 44.444, 55.555, 66.666));
	xFuzzyCoord->addTerm(new Triangle("fresco", 55.555, 66.666, 77.777));
	xFuzzyCoord->addTerm(new Triangle("gelido", 66.666, 77.777, 88.888));
	xFuzzyCoord->addTerm(new Triangle("polare", 77.777, 88.888, 100.100));

	engine->addInputVariable(xFuzzyCoord);

	//output 
	OutputVariable* fuzzyBoostCut = new OutputVariable;
	fuzzyBoostCut->setName("fuzzyBoostCut");
	fuzzyBoostCut->setDescription("Mamdani inference");
	fuzzyBoostCut->setEnabled(true);
	fuzzyBoostCut->setRange(-20.000, 20.000);
	fuzzyBoostCut->setLockValueInRange(false);
	fuzzyBoostCut->setAggregation(new Maximum);
	fuzzyBoostCut->setDefuzzifier(new Centroid(100));
	fuzzyBoostCut->setDefaultValue(0.000);//provare -> fl::nan
	fuzzyBoostCut->setLockPreviousValue(false);
	fuzzyBoostCut->addTerm(new Triangle("attenua_tanto", -20.000, -20.000, -10.000));
	fuzzyBoostCut->addTerm(new Triangle("attenua", -15.000, -10.000, -5.000));
	fuzzyBoostCut->addTerm(new Triangle("attenua_poco", -10.000, -5.000, 0.000));
	fuzzyBoostCut->addTerm(new Triangle("neutro", -5.000, 0.000, 5.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa_poco", 0.000, 5.000, 10.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa", 5.000, 10.000, 15.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa_tanto", 10.000, 15.000, 20.000));

	engine->addOutputVariable(fuzzyBoostCut);

	//Fuzzy rules
	RuleBlock* mamdani = new RuleBlock;
	mamdani->setName("mamdani");
	mamdani->setDescription("");
	mamdani->setEnabled(true);
	mamdani->setConjunction(new AlgebraicProduct);
	mamdani->setDisjunction(new AlgebraicSum);
	mamdani->setImplication(new Minimum);
	mamdani->setActivation(new General);

	mamdani->addRule(Rule::parse("if x is profondo then fuzzyBoostCut is attenua_tanto", engine));
	mamdani->addRule(Rule::parse("if x is avvolgente  then fuzzyBoostCut is attenua_tanto", engine));
	mamdani->addRule(Rule::parse("if x is morbido then fuzzyBoostCut is attenua", engine));
	mamdani->addRule(Rule::parse("if x is largo then fuzzyBoostCut is attenua_poco", engine));
	mamdani->addRule(Rule::parse("if x is ampio  then fuzzyBoostCut is neutro", engine));
	mamdani->addRule(Rule::parse("if x is arioso then fuzzyBoostCut is incrementa_poco", engine));
	mamdani->addRule(Rule::parse("if x is fresco then fuzzyBoostCut is incrementa", engine));
	mamdani->addRule(Rule::parse("if x is gelido  then fuzzyBoostCut is incrementa_poco", engine));
	mamdani->addRule(Rule::parse("if x is polare then fuzzyBoostCut is incrementa_poco", engine));

	mamdani->activate();
	engine->addRuleBlock(mamdani);

	xFuzzyCoord->setValue(x);

	engine->process();

	f8Fuzzy = fuzzyBoostCut->getValue();

	// FINE Motore per F8 ***********************************************************************************************************

}

void PluginCore::fuzzyEQUpdate9(double x, double y)
{
	//Motore per F9 ***********************************************************************************************************	
	Engine* engine = new Engine;
	engine->setName("FuzzyTouchPad");
	engine->setDescription("Motore Fuzzy GEQ");
	//Input tipo suono 
	//Input x
	InputVariable* xFuzzyCoord = new InputVariable;
	xFuzzyCoord->setName("x");
	xFuzzyCoord->setDescription("");
	xFuzzyCoord->setEnabled(true);
	xFuzzyCoord->setRange(0.000, 100.000);
	xFuzzyCoord->setLockValueInRange(false);

	xFuzzyCoord->addTerm(new Triangle("profondo", 0.000, 0.000, 11.111));
	xFuzzyCoord->addTerm(new Triangle("avvolgente", 0.000, 11.111, 22.222));
	xFuzzyCoord->addTerm(new Triangle("morbido", 11.111, 22.222, 33.333));
	xFuzzyCoord->addTerm(new Triangle("largo", 22.222, 33.333, 44.444));
	xFuzzyCoord->addTerm(new Triangle("ampio", 33.333, 44.444, 55.555));
	xFuzzyCoord->addTerm(new Triangle("arioso", 44.444, 55.555, 66.666));
	xFuzzyCoord->addTerm(new Triangle("fresco", 55.555, 66.666, 77.777));
	xFuzzyCoord->addTerm(new Triangle("gelido", 66.666, 77.777, 88.888));
	xFuzzyCoord->addTerm(new Triangle("polare", 77.777, 88.888, 100.100));

	engine->addInputVariable(xFuzzyCoord);

	//output 
	OutputVariable* fuzzyBoostCut = new OutputVariable;
	fuzzyBoostCut->setName("fuzzyBoostCut");
	fuzzyBoostCut->setDescription("Mamdani inference");
	fuzzyBoostCut->setEnabled(true);
	fuzzyBoostCut->setRange(-20.000, 20.000);
	fuzzyBoostCut->setLockValueInRange(false);
	fuzzyBoostCut->setAggregation(new Maximum);
	fuzzyBoostCut->setDefuzzifier(new Centroid(100));
	fuzzyBoostCut->setDefaultValue(0.000);//provare -> fl::nan
	fuzzyBoostCut->setLockPreviousValue(false);
	fuzzyBoostCut->addTerm(new Triangle("attenua_tanto", -20.000, -20.000, -10.000));
	fuzzyBoostCut->addTerm(new Triangle("attenua", -15.000, -10.000, -5.000));
	fuzzyBoostCut->addTerm(new Triangle("attenua_poco", -10.000, -5.000, 0.000));
	fuzzyBoostCut->addTerm(new Triangle("neutro", -5.000, 0.000, 5.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa_poco", 0.000, 5.000, 10.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa", 5.000, 10.000, 15.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa_tanto", 10.000, 15.000, 20.000));

	engine->addOutputVariable(fuzzyBoostCut);

	//Fuzzy rules
	RuleBlock* mamdani = new RuleBlock;
	mamdani->setName("mamdani");
	mamdani->setDescription("");
	mamdani->setEnabled(true);
	mamdani->setConjunction(new AlgebraicProduct);
	mamdani->setDisjunction(new AlgebraicSum);
	mamdani->setImplication(new Minimum);
	mamdani->setActivation(new General);

	mamdani->addRule(Rule::parse("if x is profondo then fuzzyBoostCut is attenua_tanto", engine));
	mamdani->addRule(Rule::parse("if x is avvolgente  then fuzzyBoostCut is attenua_tanto", engine));
	mamdani->addRule(Rule::parse("if x is morbido then fuzzyBoostCut is attenua", engine));
	mamdani->addRule(Rule::parse("if x is largo then fuzzyBoostCut is neutro", engine));
	mamdani->addRule(Rule::parse("if x is ampio  then fuzzyBoostCut is incrementa_poco", engine));
	mamdani->addRule(Rule::parse("if x is arioso then fuzzyBoostCut is incrementa", engine));
	mamdani->addRule(Rule::parse("if x is fresco then fuzzyBoostCut is incrementa", engine));
	mamdani->addRule(Rule::parse("if x is gelido  then fuzzyBoostCut is incrementa_tanto", engine));
	mamdani->addRule(Rule::parse("if x is polare then fuzzyBoostCut is incrementa", engine));

	mamdani->activate();
	engine->addRuleBlock(mamdani);

	xFuzzyCoord->setValue(x);

	engine->process();

	f9Fuzzy = fuzzyBoostCut->getValue();

	// FINE Motore per F9 ***********************************************************************************************************

}

void PluginCore::fuzzyEQUpdate10(double x, double y)
{
	//Motore per F10 ***********************************************************************************************************	
	Engine* engine = new Engine;
	engine->setName("FuzzyTouchPad");
	engine->setDescription("Motore Fuzzy GEQ");
	//Input tipo suono 
	//Input x
	InputVariable* xFuzzyCoord = new InputVariable;
	xFuzzyCoord->setName("x");
	xFuzzyCoord->setDescription("");
	xFuzzyCoord->setEnabled(true);
	xFuzzyCoord->setRange(0.000, 100.000);
	xFuzzyCoord->setLockValueInRange(false);

	xFuzzyCoord->addTerm(new Triangle("profondo", 0.000, 0.000, 11.111));
	xFuzzyCoord->addTerm(new Triangle("avvolgente", 0.000, 11.111, 22.222));
	xFuzzyCoord->addTerm(new Triangle("morbido", 11.111, 22.222, 33.333));
	xFuzzyCoord->addTerm(new Triangle("largo", 22.222, 33.333, 44.444));
	xFuzzyCoord->addTerm(new Triangle("ampio", 33.333, 44.444, 55.555));
	xFuzzyCoord->addTerm(new Triangle("arioso", 44.444, 55.555, 66.666));
	xFuzzyCoord->addTerm(new Triangle("fresco", 55.555, 66.666, 77.777));
	xFuzzyCoord->addTerm(new Triangle("gelido", 66.666, 77.777, 88.888));
	xFuzzyCoord->addTerm(new Triangle("polare", 77.777, 88.888, 100.100));

	engine->addInputVariable(xFuzzyCoord);

	//output 
	OutputVariable* fuzzyBoostCut = new OutputVariable;
	fuzzyBoostCut->setName("fuzzyBoostCut");
	fuzzyBoostCut->setDescription("Mamdani inference");
	fuzzyBoostCut->setEnabled(true);
	fuzzyBoostCut->setRange(-20.000, 20.000);
	fuzzyBoostCut->setLockValueInRange(false);
	fuzzyBoostCut->setAggregation(new Maximum);
	fuzzyBoostCut->setDefuzzifier(new Centroid(100));
	fuzzyBoostCut->setDefaultValue(0.000);//provare -> fl::nan
	fuzzyBoostCut->setLockPreviousValue(false);
	fuzzyBoostCut->addTerm(new Triangle("attenua_tanto", -20.000, -20.000, -10.000));
	fuzzyBoostCut->addTerm(new Triangle("attenua", -15.000, -10.000, -5.000));
	fuzzyBoostCut->addTerm(new Triangle("attenua_poco", -10.000, -5.000, 0.000));
	fuzzyBoostCut->addTerm(new Triangle("neutro", -5.000, 0.000, 5.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa_poco", 0.000, 5.000, 10.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa", 5.000, 10.000, 15.000));
	fuzzyBoostCut->addTerm(new Triangle("incrementa_tanto", 10.000, 15.000, 20.000));

	engine->addOutputVariable(fuzzyBoostCut);

	//Fuzzy rules
	RuleBlock* mamdani = new RuleBlock;
	mamdani->setName("mamdani");
	mamdani->setDescription("");
	mamdani->setEnabled(true);
	mamdani->setConjunction(new AlgebraicProduct);
	mamdani->setDisjunction(new AlgebraicSum);
	mamdani->setImplication(new Minimum);
	mamdani->setActivation(new General);

	mamdani->addRule(Rule::parse("if x is profondo then fuzzyBoostCut is attenua_tanto", engine));
	mamdani->addRule(Rule::parse("if x is avvolgente  then fuzzyBoostCut is attenua_tanto", engine));
	mamdani->addRule(Rule::parse("if x is morbido then fuzzyBoostCut is attenua_tanto", engine));
	mamdani->addRule(Rule::parse("if x is largo then fuzzyBoostCut is neutro", engine));
	mamdani->addRule(Rule::parse("if x is ampio  then fuzzyBoostCut is neutro", engine));
	mamdani->addRule(Rule::parse("if x is arioso then fuzzyBoostCut is incrementa_poco", engine));
	mamdani->addRule(Rule::parse("if x is fresco then fuzzyBoostCut is incrementa", engine));
	mamdani->addRule(Rule::parse("if x is gelido  then fuzzyBoostCut is incrementa_tanto", engine));
	mamdani->addRule(Rule::parse("if x is polare then fuzzyBoostCut is incrementa_tanto", engine));

	mamdani->activate();
	engine->addRuleBlock(mamdani);

	xFuzzyCoord->setValue(x);

	engine->process();

	f10Fuzzy = fuzzyBoostCut->getValue();

	// FINE Motore per F10 ***********************************************************************************************************

}

void PluginCore::updateParameters()
{	

	//X Coordinata ----------------------------------



	//Y Coordinata ----------------------------------


	//Filtro 1 
	AudioFilterParameters filterParams = f1_AudioFilter[0].getParameters();

	filterParams.fc = f_1;
	filterParams.Q = constantQ;
	filterParams.boostCut_dB = boostCut1;
	filterParams.algorithm = filterAlgorithm::kCQParaEQ;
	f1_AudioFilter[0].setParameters(filterParams);
	f1_AudioFilter[1].setParameters(filterParams);

	//Filtro 2
	filterParams = f2_AudioFilter[0].getParameters();

	filterParams.fc = f_2;
	filterParams.Q = constantQ;
	filterParams.boostCut_dB = boostCut2;
	filterParams.algorithm = filterAlgorithm::kCQParaEQ;

	f2_AudioFilter[0].setParameters(filterParams);
	f2_AudioFilter[1].setParameters(filterParams);

	//Filtro 3
	filterParams = f3_AudioFilter[0].getParameters();

	filterParams.fc = f_3;
	filterParams.Q = constantQ;
	filterParams.boostCut_dB = boostCut3;
	filterParams.algorithm = filterAlgorithm::kCQParaEQ;

	f3_AudioFilter[0].setParameters(filterParams);
	f3_AudioFilter[1].setParameters(filterParams);

	//Filtro 4
	filterParams = f4_AudioFilter[0].getParameters();

	filterParams.fc = f_4;
	filterParams.Q = constantQ;
	filterParams.boostCut_dB = boostCut4;
	filterParams.algorithm = filterAlgorithm::kCQParaEQ;

	f4_AudioFilter[0].setParameters(filterParams);
	f4_AudioFilter[1].setParameters(filterParams);

	//Filtro 5
	filterParams = f5_AudioFilter[0].getParameters();

	filterParams.fc = f_5;
	filterParams.Q = constantQ;
	filterParams.boostCut_dB = boostCut5;
	filterParams.algorithm = filterAlgorithm::kCQParaEQ;

	f5_AudioFilter[0].setParameters(filterParams);
	f5_AudioFilter[1].setParameters(filterParams);

	//Filtro 6
	filterParams = f6_AudioFilter[0].getParameters();

	filterParams.fc = f_6;
	filterParams.Q = constantQ;
	filterParams.boostCut_dB = boostCut6;
	filterParams.algorithm = filterAlgorithm::kCQParaEQ;

	f6_AudioFilter[0].setParameters(filterParams);
	f6_AudioFilter[1].setParameters(filterParams);

	//Filtro 7
	filterParams = f7_AudioFilter[0].getParameters();

	filterParams.fc = f_7;
	filterParams.Q = constantQ;
	filterParams.boostCut_dB = boostCut7;
	filterParams.algorithm = filterAlgorithm::kCQParaEQ;

	f7_AudioFilter[0].setParameters(filterParams);
	f7_AudioFilter[1].setParameters(filterParams);

	//Filtro 8
	filterParams = f8_AudioFilter[0].getParameters();

	filterParams.fc = f_8;
	filterParams.Q = constantQ;
	filterParams.boostCut_dB = boostCut8;
	filterParams.algorithm = filterAlgorithm::kCQParaEQ;

	f8_AudioFilter[0].setParameters(filterParams);
	f8_AudioFilter[1].setParameters(filterParams);

	//Filtro 9
	filterParams = f9_AudioFilter[0].getParameters();

	filterParams.fc = f_9;
	filterParams.Q = constantQ;
	filterParams.boostCut_dB = boostCut9;
	filterParams.algorithm = filterAlgorithm::kCQParaEQ;

	f9_AudioFilter[0].setParameters(filterParams);
	f9_AudioFilter[1].setParameters(filterParams);

	//Filtro 10
	filterParams = f10_AudioFilter[0].getParameters();

	filterParams.fc = f_10;
	filterParams.Q = constantQ;
	filterParams.boostCut_dB = boostCut10;
	filterParams.algorithm = filterAlgorithm::kCQParaEQ;

	f10_AudioFilter[0].setParameters(filterParams);
	f10_AudioFilter[1].setParameters(filterParams);


}

/**
\brief setup the plugin description strings, flags and codes; this is ordinarily done through the ASPiKreator or CMake

\return true if operation succeeds, false otherwise
*/
bool PluginCore::initPluginDescriptors()
{
    pluginDescriptor.pluginName = PluginCore::getPluginName();
    pluginDescriptor.shortPluginName = PluginCore::getShortPluginName();
    pluginDescriptor.vendorName = PluginCore::getVendorName();
    pluginDescriptor.pluginTypeCode = PluginCore::getPluginType();

	// --- describe the plugin attributes; set according to your needs
	pluginDescriptor.hasSidechain = kWantSidechain;
	pluginDescriptor.latencyInSamples = kLatencyInSamples;
	pluginDescriptor.tailTimeInMSec = kTailTimeMsec;
	pluginDescriptor.infiniteTailVST3 = kVSTInfiniteTail;

    // --- AAX
    apiSpecificInfo.aaxManufacturerID = kManufacturerID;
    apiSpecificInfo.aaxProductID = kAAXProductID;
    apiSpecificInfo.aaxBundleID = kAAXBundleID;  /* MacOS only: this MUST match the bundle identifier in your info.plist file */
    apiSpecificInfo.aaxEffectID = "aaxDeveloper.";
    apiSpecificInfo.aaxEffectID.append(PluginCore::getPluginName());
    apiSpecificInfo.aaxPluginCategoryCode = kAAXCategory;

    // --- AU
    apiSpecificInfo.auBundleID = kAUBundleID;   /* MacOS only: this MUST match the bundle identifier in your info.plist file */
    apiSpecificInfo.auBundleName = kAUBundleName;

    // --- VST3
    apiSpecificInfo.vst3FUID = PluginCore::getVSTFUID(); // OLE string format
    apiSpecificInfo.vst3BundleID = kVST3BundleID;/* MacOS only: this MUST match the bundle identifier in your info.plist file */
	apiSpecificInfo.enableVST3SampleAccurateAutomation = kVSTSAA;
	apiSpecificInfo.vst3SampleAccurateGranularity = kVST3SAAGranularity;

    // --- AU and AAX
    apiSpecificInfo.fourCharCode = PluginCore::getFourCharCode();
	
    return true;
}



// --- static functions required for VST3/AU only --------------------------------------------- //
const char* PluginCore::getPluginBundleName() { return kAUBundleName; }
const char* PluginCore::getPluginName(){ return kPluginName; }
const char* PluginCore::getShortPluginName(){ return kShortPluginName; }
const char* PluginCore::getVendorName(){ return kVendorName; }
const char* PluginCore::getVendorURL(){ return kVendorURL; }
const char* PluginCore::getVendorEmail(){ return kVendorEmail; }
const char* PluginCore::getAUCocoaViewFactoryName(){ return AU_COCOA_VIEWFACTORY_STRING; }
pluginType PluginCore::getPluginType(){ return kPluginType; }
const char* PluginCore::getVSTFUID(){ return kVSTFUID; }
int32_t PluginCore::getFourCharCode(){ return kFourCharCode; }
