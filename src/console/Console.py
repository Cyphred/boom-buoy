import sys
import threading
from playsound import playsound
from Setup import *
from Device import *
from Settings import *
from StationCommands import *
from ConsoleCommands import *

device = Device(sys.argv[1], 9600)
settings = Settings('settings.json')

def main():
    clear()
    version()
    verifyDevicePath()
    connectToDevice()
    #applySettingsToStation(settings, device)

    print("Enter \'help\' (without quotes) for help.")

    try:
        while True:
            command = input('>')
            parseCommand(command)

    except KeyboardInterrupt:
        properExit()

    properExit()

def parseCommand(commandString):
    if len(commandString) > 1:
        commandGroup = commandString.split(' ')

        commands = {
            "version": version,
            "help": help,
            "clear": clear,
            "cls": clear,
            "station": {
                "settings": {
                    "apply": station_settings_apply,
                    "edit": station_settings_edit,
                    "get": station_settings_get
                },
            },
            "console": {
                "settings": {
                    "save": console_settings_save,
                    "reload": console_settings_reload,
                    "edit": console_settings_edit,
                    "print": console_settings_print
                }
            },
            "debug": {
                "alarm": alarm
            }
        }

        groupLength = len(commandGroup)
        try:
            if groupLength == 1:
                commands[commandGroup[0]]()
            elif groupLength == 2:
                commands[commandGroup[0]][commandGroup[1]]()
            elif groupLength == 3:
                commands[commandGroup[0]][commandGroup[1]][commandGroup[2]]()
            else:
                print("ERROR: Too many arguments")
        except KeyError:
            print("ERROR with type KeyError")
            help()
        except TypeError:
            print("TypeError")

def invalidCommand(command):
    print(f"\'{command}\' is not a valid command.")

def version():
    # Splash info
    print("Arduino-based Dynamite Fishing Monitoring System")
    print("Version 1.0")

def help():
    print("help\t\t\t\t- Prints this menu")
    print("clear,cls\t\t\t- Clears the screen")
    print("station settings apply\t\t- Applies the current settings loaded in the console to the station.")
    print("station settings edit\t\t- Edits the current settings loaded in the console.")
    print("station settings get\t\t- Fetches the current settings loaded in the station.")
    print("cmd\t\t\t- desc")

def verifyDevicePath():
    # Verifies that a parameter has been passed
    if len(sys.argv) == 1:
        print("ERROR: No device specified. Aborting...")
        quit()

    if not devicePathExists(sys.argv[1]):
        exit()

    if not devicePathIsCOM(sys.argv[1]):
        exit();

def alarm_start():
    os.system("notify-send -u critical 'Alarm Triggered' 'Potential dynamite blast detected by buoy'")
    def playAlarm():
        os.system("mpv alarm.mp3 >/dev/null 2>&1")
    threading.Thread(target=playAlarm).start()

def connectToDevice():
    print(f"Attempting connection with {sys.argv[1]}...")
    if not authenticateWithDevice(device, 3000):
        exit()

def properExit():
    device.device.close()
    print("\nExiting...")
    exit()

def clear():
    os.system('cls' if os.name == 'nt' else 'clear')

def yesOrNo(message, defaultChoice):
    if defaultChoice:
        message += " (Yn) "
    else:
        message += " (yN) "
        
    reply = input(message)
    if not reply:
        return defaultChoice
    reply = reply.lower()
    if reply[0] == 'y':
        return True
    else:
        return False

if __name__ == "__main__":
    main()
