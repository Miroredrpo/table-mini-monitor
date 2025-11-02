## Table mini monitor 

This project is for people who costantly check there phone for something like the date, time and then see a 
notification and get lost scrolling for hours on end, this project combines a microcontroller a mini display,
a button to navigate through pages.

## components used 

1) 1x Arduino UNO R3
2) 1x 0.96" oled screen
3) 1x AHT20 sensor (for temprture and humidity)
4) 1x A DS3231 RTC module
5) 1x breadboard 
6) a few jumper cables 
7) 1x tactile pushbutton and its cover 

## 3d model

In the 3d model all i have done is made how the components will be placed into the base of the bot (which i will custom make out of paper to keep it light weight), since I am new to 3d modelling this is the best output could provide for the time consumed.

MODEL:

Top view:

<img width="296" height="631" alt="image" src="https://github.com/user-attachments/assets/04f33fe1-2bc0-4c0b-b013-db5d135bc11e" />

Front view:

<img width="748" height="475" alt="image" src="https://github.com/user-attachments/assets/133c00dd-db94-45a1-a267-0ad066a9947d" />

Rear view:

<img width="931" height="566" alt="image" src="https://github.com/user-attachments/assets/68595275-9438-41ae-aab2-88bf81eb64bb" />


## Blueprint 

I managed to sketch a blueprint sketch for this project as well this is my first time ever creating a blueprint
I think it turned out pretty good.

<img width="1250" height="889" alt="image" src="https://github.com/user-attachments/assets/f272aa7d-37bf-4a95-8ba1-609f16683298" />


## schematics 

what I have done is :  I have put in all the SDA and SCL in the same one as it should work like that and the fixed I²C address wont allow to do it in other pins unless I get a multiplexer, so i have resorted to this for now !

<img width="860" height="710" alt="image" src="https://github.com/user-attachments/assets/75d0d32a-f408-4cc5-a5d4-828ac5fc3ca5" />


## Code 

IN the code i have written the main logic of how everything will communicate with eachother, i have used about 64% of the arduino's memory/storage so, if there anything like anymore animaations or any other page you want to 
add please feel free, also update me about any cool additions as i am also very keen to make this project better.

<img width="1909" height="1029" alt="image" src="https://github.com/user-attachments/assets/f9c99c26-01b0-4310-bdb5-ccd5139200e1" />







