SERIAL_DRIVER = vendor
AUDIO_DRIVER = pwm_hardware
POINTING_DEVICE_DRIVER = analog_joystick
# No OLEDs on Mark's Unicorne build.
OLED_ENABLE = no
AUDIO_ENABLE = yes
MOUSEKEY_ENABLE = yes
ENCODER_ENABLE = yes

# markstos: enable media keys
EXTRAKEY_ENABLE = yes

# markstos: smaller file size, little down-side
LINK_TIME_OPTIMIZATION_ENABLE = yes

# markstos: for combos!
COMBO_ENABLE = yes

TAP_DANCE_ENABLE = no
