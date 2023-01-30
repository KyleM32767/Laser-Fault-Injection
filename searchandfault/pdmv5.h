#ifndef PDMv5_H
#define PDMv5_H


#include "libserialport.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_MSC_VER)
    #define PDMv5_DLL __declspec(dllexport)
#else
    #define PDMv5_DLL
#endif

//Common Fonctions
/**
 * @brief Open the communication with the device
 * @details
 * @param[in] portName The name of the COM port
 * @param[out] portPointer A pointer to a port that will be initialized correctly
 * @return A value indicating the status error (RS232 error code) = 0 if no error
 */
PDMv5_DLL enum sp_return OpenCommunication_PDMv5 (char* portName, struct sp_port **portPointer);

/**
 * @brief Close the communication with the device
 * @details
 * @param[in] port The port to close
 */
PDMv5_DLL void CloseCommunication_PDMv5 (struct sp_port *port);

/**
 * @brief Read the adress of the device
 * @details
 * @param[in] port The port used
 * @param[out] address The address of the device
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadAddress_PDMv5(struct sp_port* port, unsigned char* address);

/**
 * @brief Set the address of the device
 * @details
 * @param[in] port The port used
 * @param[in] currentAddress The current address of the device
 * @param[in] newAddress The new address of the device
 * @return An error code or 0\n
 */
PDMv5_DLL int SetAddressSpecific_PDMv5(struct sp_port* port,unsigned char currentAddress, unsigned char newAddress);

/**
 * @brief Apply values and parameters (this function must be called in order to really change the state of the PDMv5 card, it can be called after each function or after a list of functions)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @return An error code or 0\n
 */
PDMv5_DLL int ApplyRequest_PDMv5 (struct sp_port* port, unsigned char address);

/**
 * @brief Save all values into the device memory
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @return An error code or 0\n
 */
PDMv5_DLL int Save_PDMv5 (struct sp_port* port, unsigned char address);

/**
 * @brief Start a calibration
 * @details
 * Once a calibration is started, all commands will return an error code -30032 until the calibration is finished
 * Calibration IDs are :
 * - 0x00 : RESERVED
 * - 0x01 : Measure LIV (Light, Intensity, Voltage)
 * - 0x02 : Measure IP (Intensity, Power)
 * - 0x03 : Measure IV (Intensity, Voltage)
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] calibrationID The identifier of the calibration
 * @return An error code or 0\n
 */
PDMv5_DLL int StartCalibration_PDMv5 (struct sp_port* port, unsigned char address, unsigned char calibrationID);

/**
 * @brief Get the LIV Measures
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] measureStartIndex The first index of the measures that will be read
 * @param[in] measureEndIndex The last index of the measures that will be read
 * @param[out] voltages The voltages measured
 * @param[out] currents The currents measured
 * @param[out] powers The powers measured
 * @return An error code or 0\n
 */
PDMv5_DLL int GetLIVMeasures_PDMv5(struct sp_port *port, unsigned char address, unsigned short measureStartIndex, unsigned short measureEndIndex, float* voltages, float* currents, float* powers);

/**
 * @brief Get the parameters with which the LIV was done
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] currentMinimum The minimum current for the LIV (in mA)
 * @param[out] currentMaximum The maximum current for the LIV (in mA)
 * @param[out] currentStep The current step for the LIV (in mA)
 * @param[out] pauseInterval The pause interval for the LIV (in ms)
 * @param[out] count The number of the measures
 * @param[out] photodiode The photodiode used, 0 for BFM, 1 for PD_EXT
 * @return An error code or 0\n
 */
PDMv5_DLL int GetLIVParameters_PDMv5(struct sp_port *port, unsigned char address, float* currentMinimum, float* currentMaximum, float* currentStep, float* pauseInterval, unsigned char* count, unsigned char* photodiode);



// =============================================================================
// System Configuration

/**
 * @brief Read the hardware type
 * @details
 * - 'A' is for PDM
 * - 'B' is for MMD
 * - 'C' is for Cristal
 * - 'D' is for Central
 * - 'E' is for Pulsepicker
 * - 'F' is for Shaper
 * - 'G' is for PDMv5
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] type An integer corresponding to the hardware type
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadHardwareType_PDMv5 (struct sp_port* port, unsigned char address, unsigned int *type);

/**
 * @brief Read the hardware version
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] version Three integers corresponding to the hardware version
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadHardwareVersion_PDMv5 (struct sp_port* port, unsigned char address, unsigned char* version);

/**
 * @brief Read the serial number
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] serial An integer corresponding to the serial number
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadSerialNumber_PDMv5 (struct sp_port* port, unsigned char address, unsigned int *serial);

/**
 * @brief Read the software type
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] type An integer corresponding to the software type
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadSoftwareType_PDMv5 (struct sp_port* port, unsigned char address, unsigned int *type);

/**
 * @brief Read the software version
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] version 3 integers corresponding to the software version
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadSoftwareVersion_PDMv5 (struct sp_port* port, unsigned char address, unsigned char* version);

/**
 * @brief Read the synchronisation line which will trigger pulses
 * @details
 * 0 : External TTL/LVTTL (SMA input), 1: External LVDS (optional SMA inputs), 2 : Internal clock
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] mode The synchronisation line
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadSynchro_PDMv5 (struct sp_port* port, unsigned char address, unsigned char* mode);

/**
 * @brief Read the delay line
 * @details
 * 0 : NONE (SMA TTL/LVTTL input, duration of pulses will be the same as the applied signal), 1: Internal
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] mode The delay line
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadDelayLine_PDMv5 (struct sp_port* port, unsigned char address, unsigned char* mode);

/**
 * @brief Set the delay line
 * @details
 * 0 : NONE (SMA TTL/LVTTL input, duration of pulses will be the same as the applied signal), 1: Internal
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] mode The delay line
 * @return An error code or 0\n
 */
PDMv5_DLL int SetDelayLine_PDMv5 (struct sp_port* port, unsigned char address, unsigned char mode);

/**
 * @brief Read the frequency (in Hz)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] frequency The frequency (in Hz)
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadFrequency_PDMv5 (struct sp_port* port, unsigned char address, unsigned int* frequency);

/**
 * @brief Set the frequency (in Hz)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] frequency The frequency (in Hz)
 * @return An error code or 0\n
 */
PDMv5_DLL int SetFrequency_PDMv5 (struct sp_port* port, unsigned char address, unsigned int frequency);

/**
 * @brief Read the pulse width (in ps)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] width The pulse width (in ps)
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadPulseWidth_PDMv5 (struct sp_port* port, unsigned char address, unsigned int* width);

/**
 * @brief Set the pulse width (in ps)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] width The pulse width (in ps)
 * @return An error code or 0\n
 */
PDMv5_DLL int SetPulseWidth_PDMv5 (struct sp_port* port, unsigned char address, unsigned int width);

/**
 * @brief Read the delay (in ps)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] delay The delay (in ps)
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadDelay_PDMv5 (struct sp_port* port, unsigned char address, unsigned int* delay);

/**
 * @brief Set the delay (in ps)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] delay The delay (in ps)
 * @return An error code or 0\n
 */
PDMv5_DLL int SetDelay_PDMv5 (struct sp_port* port, unsigned char address, unsigned int delay);

/**
 * @brief Read the current (in % of maximum current)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] current The current (in % of maximum current)
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadCurrent_PDMv5 (struct sp_port* port, unsigned char address, float* current);

/**
 * @brief Set the current (in % of maximum current)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] current The current (in % of maximum current)
 * @return An error code or 0\n
 */
PDMv5_DLL int SetCurrent_PDMv5 (struct sp_port* port, unsigned char address, float current);

/**
 * @brief Read the temperature (in °C)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] temperature The temperature (in °C)
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadTemperature_PDMv5 (struct sp_port* port, unsigned char address, float* temperature);

/**
 * @brief Set the temperature (in °C)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] temperature The temperature (in °C)
 * @return An error code or 0\n
 */
PDMv5_DLL int SetTemperature_PDMv5 (struct sp_port* port, unsigned char address, float temperature);

/**
 * @brief Read the mean current limit (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] current The mean current limit (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadMaximumAverageCurrent_PDMv5 (struct sp_port* port, unsigned char address, float* current);

/**
 * @brief Set the mean current limit (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] current The mean current limit (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int SetMaximumAverageCurrent_PDMv5 (struct sp_port* port, unsigned char address, float current);

/**
 * @brief Read the maximum current limit (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] current The maximum current limit (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadMaximumCurrent_PDMv5 (struct sp_port* port, unsigned char address, float* current);

/**
 * @brief Set the maximum current limit (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] current The maximum current limit (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int SetMaximumCurrent_PDMv5 (struct sp_port* port, unsigned char address, float current);

/**
 * @brief Read the laser status
 * @details
 * 0 for OFF, 1 for ON
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] status The laser status
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadLaserStatus_PDMv5 (struct sp_port* port, unsigned char address, unsigned char* status);

/**
 * @brief Set the laser status
 * @details
 * 0 for OFF, 1 for ON
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] status The laser status
 * @return An error code or 0\n
 */
PDMv5_DLL int SetLaserStatus_PDMv5 (struct sp_port* port, unsigned char address, unsigned char status);

//************************************************************************//

/**
 * @brief Read TEC maximum current (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] current The TEC maximum current (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadTECMaximumCurrent_PDMv5 (struct sp_port* port, unsigned char address, float *current);

/**
 * @brief Set the TEC maximum current (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] current The TEC maximum current (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int SetTECMaximumCurrent_PDMv5 (struct sp_port* port, unsigned char address, float current);

/**
 * @brief Read the TEC maximum voltage (in mV)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] voltage The TEC maximum voltage (in mV)
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadTECMaximumVoltage_PDMv5 (struct sp_port* port, unsigned char address, float *voltage);

/**
 * @brief Set the TEC maximum voltage (in mV)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] voltage The TEC maximum voltage (in mV)
 * @return An error code or 0\n
 */
PDMv5_DLL int SetTECMaximumVoltage_PDMv5 (struct sp_port* port, unsigned char address, float voltage);

/**
 * @brief Read The Compliance Voltage
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] voltage The Compliance Voltage
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadComplianceVoltage_PDMv5 (struct sp_port* port, unsigned char address, float *voltage);

/**
 * @brief Set the compliance voltage (in V)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] voltage The compliance voltage (in V)
 * @return An error code or 0\n
 */
PDMv5_DLL int SetComplianceVoltage_PDMv5 (struct sp_port* port, unsigned char address, float voltage);

/**
 * @brief Read the operating mode
 * @details
 * 0 : ACC, 1 : APC
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] mode The operating mode
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadOperatingMode_PDMv5 (struct sp_port* port, unsigned char address, unsigned char *mode);

/**
 * @brief Set the operating mode
 * @details
 * 0 : ACC, 1 : APC
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] mode The operating mode
 * @return An error code or 0\n
 */
PDMv5_DLL int SetOperatingMode_PDMv5 (struct sp_port* port, unsigned char address, unsigned char mode);

/**
 * @brief Read the APC photodiode
 * @details
 * 0 : BFM, 1 : PD_EXT
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] mode The APC photodiode
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadAPCPhotodiode_PDMv5 (struct sp_port* port, unsigned char address, unsigned char *mode);

/**
 * @brief Set the APC photodiode
 * @details
 * 0 : BFM, 1 : PD_EXT
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] mode The APC photodiode
 * @return An error code or 0\n
 */
PDMv5_DLL int SetAPCPhotodiode_PDMv5 (struct sp_port* port, unsigned char address, unsigned char mode);

/**
 * @brief Read the APC sampling period (in ms)
 * @details
 * 0 : BFM, 1 : PD_EXT
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] time The APC sampling period (in ms)
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadAPCSamplingPeriod_PDMv5 (struct sp_port* port, unsigned char address, unsigned short *time);

/**
 * @brief Set the APC sampling period (in ms)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] time The APC sampling period (in ms)
 * @return An error code or 0\n
 */
PDMv5_DLL int SetAPCSamplingPeriod_PDMv5 (struct sp_port* port, unsigned char address, unsigned short time);

/**
 * @brief Read the APC hysteresis percentage (in %)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] percentage The APC hysteresis percentage (in %)
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadAPCHysteresisPercentage_PDMv5 (struct sp_port* port, unsigned char address, float *percentage);

/**
 * @brief Set the APC hysteresis percentage (in %)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] percentage The APC hysteresis percentage (in %)
 * @return An error code or 0\n
 */
PDMv5_DLL int SetAPCHysteresisPercentage_PDMv5 (struct sp_port* port, unsigned char address, float percentage);

/**
 * @brief Read the pulse laser status
 * @details
 * 0 : OFF, 1 : ON
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] status The pulsedd mode laser status
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadPulseLaserStatusPDMv5 (struct sp_port* port, unsigned char address, unsigned char *status);

/**
 * @brief Set the pulse laser status
 * @details
 * 0 : OFF, 1 : ON
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] status The pulse laser status
 * @return An error code or 0\n
 */
PDMv5_DLL int SetPulseLaserStatus_PDMv5 (struct sp_port* port, unsigned char address, unsigned char status);

/**
 * @brief Read the pulse current source
 * @details
 * 0 : Internal DAC; 1 : Potentiometer POT; 2 : External (SMA or connector)
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] source The pulse current source
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadPulseCurrentSource_PDMv5 (struct sp_port* port, unsigned char address, unsigned char *source);

/**
 * @brief Set the pulse current source
 * @details
 * 0 : Internal DAC; 1 : Potentiometer POT; 2 : External (SMA or connector)
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] source The pulse current source
 * @return An error code or 0\n
 */
PDMv5_DLL int SetPulseCurrentSource_PDMv5 (struct sp_port* port, unsigned char address, unsigned char source);

/**
 * @brief Read the PULSE_IN detection threshold (in mV)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] voltage The PULSE_IN detection threshold (in mV)
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadPULSE_INDetectionThreshold_PDMv5 (struct sp_port* port, unsigned char address, float *voltage);

/**
 * @brief Set the PULSE_IN detection threshold (in mV)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] voltage The PULSE_IN detection threshold (in mV)
 * @return An error code or 0\n
 */
PDMv5_DLL int SetPULSE_INDetectionThreshold_PDMv5 (struct sp_port* port, unsigned char address, float voltage);

/**
 * @brief Read the CW laser status
 * @details
 * 0 : OFF, 1 : ON
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] status The CW laser status
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadCWLaserStatus_PDMv5 (struct sp_port* port, unsigned char address, unsigned char *status);

/**
 * @brief Set the CW laser status
 * @details
 * 0 : OFF, 1 : ON
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] status The CW laser status
 * @return An error code or 0\n
 */
PDMv5_DLL int SetCWLaserStatus_PDMv5 (struct sp_port* port, unsigned char address, unsigned char status);

/**
 * @brief Read the CW current source
 * @details
 * 0 : Internal DAC; 1 : Potentiometer POT; 2 : External (SMA or connector)
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] status The CW current source
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadCWCurrentSource_PDMv5 (struct sp_port* port, unsigned char address, unsigned char *status);

/**
 * @brief Set the CW current source
 * @details
 * 0 : Internal DAC; 1 : Potentiometer POT; 2 : External (SMA or connector)
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] status The CW current source
 * @return An error code or 0\n
 */
PDMv5_DLL int SetCWCurrentSource_PDMv5 (struct sp_port* port, unsigned char address, unsigned char status);

/**
 * @brief Read the CW maximum current (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] current The CW maximum current (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadCWMaximumCurrent_PDMv5 (struct sp_port* port, unsigned char address, float *current);

/**
 * @brief Set the CW maximum current (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] current The CW maximum current (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int SetCWMaximumCurrent_PDMv5 (struct sp_port* port, unsigned char address, float current);

/**
 * @brief Read the CW current (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] current The CW current (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadCWCurrent_PDMv5 (struct sp_port* port, unsigned char address, float *current);

/**
 * @brief Set the CW current (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] current The CW current (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int SetCWCurrent_PDMv5 (struct sp_port* port, unsigned char address, float current);

/**
 * @brief Read the modulation status
 * @details
 * 0 : Off; 1 : On
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] status modulation status
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadModulationStatus_PDMv5 (struct sp_port* port, unsigned char address, unsigned char *status);

/**
 * @brief Set the modulation status
 * @details
 * 0 : Off; 1 : On
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] status The modulation status
 * @return An error code or 0\n
 */
PDMv5_DLL int SetModulationStatus_PDMv5 (struct sp_port* port, unsigned char address, unsigned char status);

/**
 * @brief Read the maximum modulation current (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] current The maximum modulation current (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadModulationMaximumCurrent_PDMv5 (struct sp_port* port, unsigned char address, float *current);

/**
 * @brief Set the maximum modulation current (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] current The maximum modulation current (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int SetModulationMaximumCurrent_PDMv5 (struct sp_port* port, unsigned char address, float current);

/**
 * @brief Read the modulation current (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] current The modulation current (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadModulationCurrent_PDMv5 (struct sp_port* port, unsigned char address, float *current);

/**
 * @brief Set the modulation current (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] current The modulation current (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int SetModulationCurrent_PDMv5 (struct sp_port* port, unsigned char address, float current);

/**
 * @brief Read the internal modulation type
 * @details
 * 0 : Sinusoidal, 1 : Triangular, 2 : Square
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] type The internal modulation type
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadModulationInternalType_PDMv5 (struct sp_port* port, unsigned char address, unsigned char *type);

/**
 * @brief Set the internal modulation type
 * @details
 * 0 : Sinusoidal, 1 : Triangular, 2 : Square
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] type The internal modulation type
 * @return An error code or 0\n
 */
PDMv5_DLL int SetModulationInternalType_PDMv5 (struct sp_port* port, unsigned char address, unsigned char type);

/**
 * @brief Read the modulation frequency
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] frequency The modulation frequency (in Hz)
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadModulationFrequency_PDMv5 (struct sp_port* port, unsigned char address, float *frequency);

/**
 * @brief Set the modulation frequency (in Hz)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] frequency The modulation frequency (in Hz)
 * @return An error code or 0\n
 */
PDMv5_DLL int SetModulationFrequency_PDMv5 (struct sp_port* port, unsigned char address, float frequency);

/**
 * @brief Read the external modulation current gain
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] gain The external modulation current gain (in mA/V)
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadModulationExternalCurrentGain_PDMv5 (struct sp_port* port, unsigned char address, float *gain);

/**
 * @brief Set the gain external modulation current
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] gain The gain external modulation current (in mA/V)
 * @return An error code or 0\n
 */
PDMv5_DLL int SetModulationExternalCurrentGain_PDMv5 (struct sp_port* port, unsigned char address, float gain);

/**
 * @brief Read the LIV pause interval
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] time the LIV pause interval (in ms)
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadLIVPauseInterval_PDMv5 (struct sp_port* port, unsigned char address, float *time);

/**
 * @brief Set the LIV pause interval
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] time The LIV pause interval (in ms)
 * @return An error code or 0\n
 */
PDMv5_DLL int SetLIVPauseInterval_PDMv5 (struct sp_port* port, unsigned char address, float time);

/**
 * @brief Read the LIV measures count
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] value The LIV measures count
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadLIVMeasuresCount_PDMv5 (struct sp_port* port, unsigned char address, unsigned char *value);

/**
 * @brief Set the LIV measures count
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] value The LIV measures count
 * @return An error code or 0\n
 */
PDMv5_DLL int SetLIVMeasuresCount_PDMv5 (struct sp_port* port, unsigned char address, unsigned char value);

/**
 * @brief Read the LIV current step (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] current The LIV current step (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadLIVCurrentStep_PDMv5 (struct sp_port* port, unsigned char address, float *current);

/**
 * @brief Set the LIV current step (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] current The LIV current step (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int SetLIVCurrentStep_PDMv5 (struct sp_port* port, unsigned char address, float current);

/**
 * @brief Read the LIV minimum current (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] current The LIV minimum current (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadLIVMinimumCurrent_PDMv5 (struct sp_port* port, unsigned char address, float *current);

/**
 * @brief Set the LIV minimum current (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] current The LIV minimum current (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int SetLIVMinimumCurrent_PDMv5 (struct sp_port* port, unsigned char address, float current);

/**
 * @brief Read the LIV maximum current (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] current The LIV maximum current (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadLIVMaximumCurrent_PDMv5 (struct sp_port* port, unsigned char address, float *current);

/**
 * @brief Set the LIV maximum current (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] current The LIV maximum current (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int SetLIVMaximumCurrent_PDMv5 (struct sp_port* port, unsigned char address, float current);

/**
 * @brief Read the LIV photodiode choice
 * @details 0 for BFM, 1 for PD_EXT
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] photodiode The LIV photodiode choice
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadLIVPhotodiode_PDMv5 (struct sp_port* port, unsigned char address, unsigned char *photodiode);

/**
 * @brief Set the LIV photodiode choice
 * @details 0 for BFM, 1 for PD_EXT
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] photodiode The LIV photodiode choice
 * @return An error code or 0\n
 */
PDMv5_DLL int SetLIVPhotodiode_PDMv5 (struct sp_port* port, unsigned char address, unsigned char photodiode);

/**
 * @brief Read the LIV pulse width (in ms)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] time The LIV pulse width (in ms)
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadLIVPulseWidth_PDMv5 (struct sp_port* port, unsigned char address, float *time);

/**
 * @brief Set the LIV pulse width (in ms)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] time The LIV pulse width (in ms)
 * @return An error code or 0\n
 */
PDMv5_DLL int SetLIVPulseWidth_PDMv5 (struct sp_port* port, unsigned char address, float time);

/**
 * @brief Read the BFM gain
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] gain The BFM gain
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadBFMGain_PDMv5 (struct sp_port* port, unsigned char address, float *gain);

/**
 * @brief Set the BFM gain
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] gain The BFM gain
 * @return An error code or 0\n
 */
PDMv5_DLL int SetBFMGain_PDMv5 (struct sp_port* port, unsigned char address, float gain);

/**
 * @brief Read the PD_EXT photodiode gain
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] gain The PD_EXT photodiode gain
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadPD_EXTGain_PDMv5 (struct sp_port* port, unsigned char address, float *gain);

/**
 * @brief Set the PD_EXT photodiode gain
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] gain The PD_EXT photodiode gain
 * @return An error code or 0\n
 */
PDMv5_DLL int SetPD_EXTGain_PDMv5 (struct sp_port* port, unsigned char address, float gain);

/**
 * @brief Read the external multielements board command voltage (in mV)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] voltage The external multielements board command voltage (in mV)
 * @return An error code or 0\n
 */
PDMv5_DLL int ReadExternalMultiElementsBoardCommandVoltage_PDMv5 (struct sp_port* port, unsigned char address, unsigned short *voltage);

/**
 * @brief Set the external multielements board command voltage (in mV)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[in] voltage The external multielements board command voltage (in mV)
 * @return An error code or 0\n
 */
PDMv5_DLL int SetExternalMultiElementsBoardCommandVoltage_PDMv5 (struct sp_port* port, unsigned char address, unsigned short voltage);




//MEASURES





/**
 * @brief Read the key status
 * @details
 * 0 : UNTURNED, 1 : TURNED
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] status The key status
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasureKeyStatus_PDMv5(struct sp_port *port, unsigned char address, unsigned char *status);

/**
 * @brief Read the BNC interlock status
 * @details
 * 0 : OFF, 1 : ON
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] status The BNC interlock status
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasureBNCInterlockStatus_PDMv5(struct sp_port *port, unsigned char address, unsigned char *status);

/**
 * @brief Read the external interlock status
 * @details
 * 0 : OFF, 1 : ON
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] status The external interlock status
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasureEXTInterlockStatus_PDMv5(struct sp_port *port, unsigned char address, unsigned char *status);

/**
 * @brief Read the LIV status (in %)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] percentage The LIV status (in %)
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasureLIVStatus_PDMv5(struct sp_port *port, unsigned char address, unsigned int *percentage);

/**
 * @brief Read the measured peak current consign (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] current The measured peak current consign (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasurePeakCurrentConsign_PDMv5(struct sp_port *port, unsigned char address, float *current);

/**
 * @brief Read the measured CW consign (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] current The measured CW consign (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasureCWCurrentConsign_PDMv5(struct sp_port *port, unsigned char address, float *current);

/**
 * @brief Read the measured temperature consign (in °C)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] temperature The measured temperature consign (in °C)
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasureTemperatureConsign_PDMv5(struct sp_port *port, unsigned char address, float *temperature);

/**
 * @brief Read the measured diode temperature (in °C)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] temperature The measured diode temperature (in °C)
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasureDiodeTemperature_PDMv5(struct sp_port *port, unsigned char address, float *temperature);

/**
 * @brief Read the measured TEC Voltage reference (in mV)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] voltage The measured TEC Voltage reference (in mV)
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasureTECVoltageReference_PDMv5(struct sp_port *port, unsigned char address, float *voltage);

/**
 * @brief Read the measured TEC Current (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] current The measured TEC Current (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasureTECCurrent_PDMv5(struct sp_port *port, unsigned char address, float *current);

/**
 * @brief Read the measured TEC external temperature (in °C)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] temperature The measured TEC external temperature (in °C)
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasureTECExternalTemperature_PDMv5(struct sp_port *port, unsigned char address, float *temperature);

/**
 * @brief Read the measured MOS temperature (in °C)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] temperature The measured MOS temperature (in °C)
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasureMOSTemperature_PDMv5(struct sp_port *port, unsigned char address, float *temperature);

/**
 * @brief Read the measured TEC Voltage (in mV)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] voltage The measured TEC Voltage (in mV)
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasureTECVoltage_PDMv5(struct sp_port *port, unsigned char address, float *voltage);

/**
 * @brief Read the measured diode voltage (in V)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] voltage The measured diode voltage (in V)
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasureDiodeVoltage_PDMv5(struct sp_port *port, unsigned char address, float * voltage);

/**
 * @brief Read the measured diode CW current (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] current The measured diode CW current (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasureDiodeCWCurrent_PDMv5(struct sp_port *port, unsigned char address, float *current);

/**
 * @brief Read the measured diode average current (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] current The measured diode average current (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasureDiodeAverageCurrent_PDMv5(struct sp_port *port, unsigned char address, float * current);

/**
 * @brief Read the measured diode pulsed current (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] current The measured diode pulsed current (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasureDiodePulsedCurrent_PDMv5(struct sp_port *port, unsigned char address, float * current);

/**
 * @brief Read the measured BFM current (in µA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] current The measured BFM current (in µA)
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasureBFMCurrent_PDMv5(struct sp_port *port, unsigned char address, float * current);

/**
 * @brief Read the measured PD_EXT current (in µA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] current The measured PD_EXT current (in µA)
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasurePD_EXTCurrent_PDMv5(struct sp_port *port, unsigned char address, float *current);

/**
 * @brief Read the Central Driver enable status
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] status The Central Driver enable status
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasureCentralDriverEnableStatus_PDMv5(struct sp_port *port, unsigned char address, unsigned char *status);

/**
 * @brief Read the Central MMD enable status
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] status The Central MMD enable status
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasureCentralMMDEnableStatus_PDMv5(struct sp_port *port, unsigned char address, unsigned char *status);

/**
 * @brief Read the measured patch board TEC external temperature (in °C)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] temperature The measured patch board TEC external temperature (in °C)
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasurePatchTECExternalTemperature_PDMv5(struct sp_port *port, unsigned char address, float *temperature);

/**
 * @brief Read the measured patch board PICOLAS current (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] current The measured patch board PICOLAS current (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasurePatchPICOLASCurrent_PDMv5(struct sp_port *port, unsigned char address, float *current);

/**
 * @brief Read the measured patch board PICOLAS compliance voltage (in V)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] voltage The measured patch board PICOLAS compliance voltage (in V)
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasurePatchPICOLASComplianceVoltage_PDMv5(struct sp_port *port, unsigned char address, float *voltage);

/**
 * @brief Read the measured patch board TEC current (in mA)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] current The measured patch board TEC current (in mA)
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasurePatchTECCurrent_PDMv5(struct sp_port *port, unsigned char address, float *current);

/**
 * @brief Read the measured patch board ALIM battery voltage (in V)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] voltage The measured patch board ALIM battery voltage (in V)
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasurePatchBatteryVoltage_PDMv5(struct sp_port *port, unsigned char address, float *voltage);

/**
 * @brief Read the measured input voltage (in V)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] voltage The measured input voltage (in V)
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasureInputVoltage_PDMv5(struct sp_port *port, unsigned char address, float *voltage);

/**
 * @brief Read the measured compliance voltage (in V)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] voltage The measured compliance voltage (in V)
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasureComplianceVoltage_PDMv5(struct sp_port *port, unsigned char address, float *voltage);

/**
 * @brief Read the 5V alimentation voltage (in V)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] voltage The 5V alimentation voltage (in V)
 * @return An error code or 0\n
 */
PDMv5_DLL int Measure5VPositiveVoltage_PDMv5(struct sp_port *port, unsigned char address, float *voltage);

/**
 * @brief Read the 3.3V alimentation voltage (in V)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] voltage The 3.3V alimentation voltage (in V)
 * @return An error code or 0\n
 */
PDMv5_DLL int Measure3V3PositiveVoltage_PDMv5(struct sp_port *port, unsigned char address, float *voltage);

/**
 * @brief Read the 2.5V alimentation voltage (in V)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] voltage The 2.5V alimentation voltage (in V)
 * @return An error code or 0\n
 */
PDMv5_DLL int Measure2V5PositiveVoltage_PDMv5(struct sp_port *port, unsigned char address, float *voltage);

/**
 * @brief Read the 1.3V alimentation voltage (in V)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] voltage The 1.3V alimentation voltage (in V)
 * @return An error code or 0\n
 */
PDMv5_DLL int Measure1V3PositiveVoltage_PDMv5(struct sp_port *port, unsigned char address, float *voltage);

/**
 * @brief Read the -5V alimentation voltage (in V)
 * @details
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] voltage The -5V alimentation voltage (in V)
 * @return An error code or 0\n
 */
PDMv5_DLL int Measure5VNegativeVoltage_PDMv5(struct sp_port *port, unsigned char address, float *voltage);

/**
 * @brief Read the alarms
 * @details Each alarm is coded by a bit
 * 			- b0 : Interlock
 * 			- b1 : Average Current
 * 			- b2 : Diode Temperature
 * 			- b3 : ICHG Temperature (CW mode) or MOS Temperature (Pulsed mode)
 * 			- b4 : TEC Ext
 * 			- b5 : BNC Interlock
 * 			- b6 : Ext Interlock
 * 			- b7 : Key Interlock
 * 			- b8 : MOS CW
 * 			- b9 : Reserved
 * 			- b10 : Open Circuit
 * @param[in] port The port used
 * @param[in] address The address of the device
 * @param[out] alarms The alarms
 * @return An error code or 0\n
 */
PDMv5_DLL int MeasureAlarms_PDMv5(struct sp_port *port, unsigned char address, unsigned int *alarms);

#ifdef __cplusplus
}
#endif

#endif // PDMv5_H
