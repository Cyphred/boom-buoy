import Console
import json

def console_settings_save():
    if Console.yesOrNo("Are you sure you want to overwrite the settings file?", False):
        print(f"Saving settings to \'{Console.settings.filePath}\'...")
        Console.settings.save()
    
def console_settings_reload():
    if Console.yesOrNo("Are you sure you want to reload from the settings file? Any unsaved changes will be lost.", False):
        print(f"Reloading settings from \'{Console.settings.filePath}\'...")
        Console.settings.load()
    
def console_settings_edit():
    print("edit console settings")

def console_settings_print():
    print("Settings loaded in console:")
    timeout = Console.settings.data['buoy_settings']['ping_timeout']
    mode = Console.settings.data['buoy_settings']['mode']
    variance = Console.settings.data['buoy_settings']['variance_threshold']
    interval = Console.settings.data['buoy_settings']['measurement_interval']
    print(f"  Mode: {mode}")
    print(f"  Measurement Interval: {interval}ms")
    print(f"  Ping Timeout: {timeout}ms")
    print(f"  Variance Threshold: {variance}%")
