#ifndef MICEWARS_GLOBAL_VARS_H
#define MICEWARS_GLOBAL_VARS_H

enum {  gravity = 0,
        movement = 1,
        left = -1,
        stay = 0,
        right = 1   };

#define GREEN   0x95C355
#define BLUE    0x3885E7
#define MICE_WIDTH  25
#define MICE_HEIGHT 25

#define AMOUNT_OF_CHEESE_HOLES   18
#define RIVER_DIVIDER            7

#define MOUSE1_IMG               "img/mouse.png"
#define MOUSE_MOVEPOINTS         250
#define MICE_SPEED_MUL           100
#define GRAVITY_MUL              150
#define HILL_OVERCOME_PIXELS     20

#define NOTIFICATION_HP_OFFSET   20
#define NOTIFICATION_HP_WIDTH    25
#define NOTIFICATION_HP_HEIGHT   20
#define NOTIFICATIONBOX_FONTSIZE 20

#endif //MICEWARS_GLOBAL_VARS_H
