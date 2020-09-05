// this is sort of a C equivalent of:
//  https://github.com/dmanlfc/arcade1up/blob/master/volume.py

// But this C code is public domain.  --ryan.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>

int main(int argc, char **argv)
{
    int volumeState = 999;   /* force volume to be set at startup */

    wiringPiSetupPhys();

    pullUpDnControl(12, PUD_UP);
    pullUpDnControl(16, PUD_DOWN);

    while (1) {
        const int buttonState1 = digitalRead(12);
        const int buttonState2 = digitalRead(16);

        if (!buttonState1 && !buttonState2 && (volumeState != 99)) {
            printf("Switch was set to Vol HIGH (volstate %d => 99)\n", volumeState);
            system("amixer set HDMI unmute");
            system("amixer set HDMI 99%");
            volumeState = 99;
        } else if (buttonState1 && buttonState2 && (volumeState != 0)) {
            printf("Switch was set to MUTE (volstate %d => 0)\n", volumeState);
            system("amixer set HDMI mute");
            volumeState = 0;
        } else if (buttonState1 && !buttonState2 && (volumeState != 80)) {
            printf("Switch was set to Vol LOW (volstate %d => 80)\n", volumeState);
            system("amixer set HDMI unmute");
            system("amixer set HDMI 80%");
            volumeState = 80;
        } else {
            usleep(300 * 1000);
        }
    }

    return 0;
}

// end of arcade1up-volume-gpio.c ...

