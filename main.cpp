#include <joypad.hpp>
#include <config.hpp>
#include <iostream>

auto config = getConfig();

bool enable = true;
bool tgd = false;

bool vUp_btn = false;
bool vDown_btn = false;

void handleToggle(input_event &ev)
{
    if (ev.code == KEY_VOLUMEDOWN)
        vUp_btn = ev.value;
    if (ev.code == KEY_VOLUMEUP)
        vDown_btn = ev.value;

    if (vUp_btn && vDown_btn)
    {
        if (!tgd)
        {
            enable = !enable;

            tgd = true;
        }
    }
    else
        tgd = false;
}

void x55()
{
    inputDevice inabs("/dev/input/event1");
    inputDevice incon("/dev/input/event3");
    inputDevice invol("/dev/input/event4");

    input_event ev;

    while (true)
    {
        usleep(6400);

        while (inabs.manPull(ev) == 0)
        {
            if (!enable)
                forwardGamepad(ev.type, ev.code, ev.value);

            if (ev.type == EV_ABS)
            {
                if (enable)
                    handleABS(ev);
            }
        }

        while (incon.manPull(ev) == 0)
        {
            if (ev.type == EV_ABS && (ev.code == ABS_RY || ev.code == ABS_Y))
                    ev.value = 1000 - ev.value; // for whatever reason the y axis are swapper
            
            if (!enable){
                forwardGamepad(ev.type, ev.code, ev.value);
            }
                

            if (enable && ev.type == EV_KEY)
                handleCont(ev);
        }

        while (invol.manPull(ev) == 0)
        {
            if (ev.type == EV_KEY)
            {
                handleToggle(ev);
            }
        }

        if (enable)
        {
            handleMouse();
        }
    }
}
void rg552()
{
    inputDevice inabs("/dev/input/event1");
    inputDevice incon("/dev/input/event3");
    inputDevice invol("/dev/input/event4");

    input_event ev;

    while (true)
    {
        usleep(6400);

        while (inabs.manPull(ev) == 0)
        {
            if (!enable)
                forwardGamepad(ev.type, ev.code, ev.value);

            if (ev.type == EV_ABS)
            {
                if (enable)
                    handleABS(ev);
            }
        }

        while (incon.manPull(ev) == 0)
        {
            if (ev.type == EV_ABS && (ev.code == ABS_RY || ev.code == ABS_Y))
                    ev.value = 1000 - ev.value; // for whatever reason the y axis are swapper
            
            if (!enable){
                forwardGamepad(ev.type, ev.code, ev.value);
            }
                

            if (enable && ev.type == EV_KEY)
                handleCont(ev);
        }

        while (invol.manPull(ev) == 0)
        {
            if (ev.type == EV_KEY)
            {
                handleToggle(ev);
            }
        }

        if (enable)
        {
            handleMouse();
        }
    }
}

int main(int argc, char *argv[]){

    if(config["device"]=="x55"){
        std::cout << "Device : x55" << std::endl;
        x55();
        return 0;   
    }

    if(config["device"]=="rg552"){
        std::cout << "Device : x552" << std::endl;
        rg552();
        return 0;
    }

    std::cout << "unknown device" << std::endl;
}