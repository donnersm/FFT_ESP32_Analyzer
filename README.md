** important update: If your display doesn't respond well to the microphone input, you can adjust resistor R10,( The lower the value, the better the amplification) infact,you can remove it and replace it by a wire or some soldering tin. I did it on my prototype and result is amazing

# FFT_ESP32_Analyzer
Spectrum analyzer 8-64channels FFT


8-64 Channel FFT Spectrum Analyzer
-	Line in Audio
-	Mic in Audio
-	8,16,24,32 or 64 channels
-	Different patterns and colors
-	Adjustable Peak Delay time
-	Selectable input filter
-	Auto change of patterns every few seconds ( can be set to on/off)
-	Based on ESP32
-	PCB available with onboard pre-amplifier and connector or HUB75 Displays
-	Can drive ledstrip like WS2812 and similar 
-	Can drive series of HUB75€ Panels
-	Adjustable overall brightness
PCB available with SMD components pre-assembled. You will only need to add the ESP32 board and the connectors / opamp and sockets.
Schematic and PCB layout and gerber files( PCB production files) available
Work in progress:
Future firmware update will include:
-	Smooth LED transition as the LEDS are so fast it will follow the datastream. I want to implement a sort of afterglow on each led when it turns of. That will moving bars will look less hectic.
-	Web interface, I would like to output data on wifi to visualize the spectrum live on a webbrowser. Although technically this already has been done, the challenge will be the use of the ADC's at the same time. Those of you who know the architecture of the ESP32 will now what I mean.
-	Changing the number of bands runtime unlike now it is done before compiling and can only be changed by uploading the firmware with changed parameters.
-	Elaborate and automize the calibration modes.


See Manual4.0.pdf for more details and information
