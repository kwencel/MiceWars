#ifndef MICEWARS_GLOBAL_VARS_H
#define MICEWARS_GLOBAL_VARS_H

enum {  gravity = 0,
        movement = 1,
        left = -1,
        stay = 0,
        right = 1,
        shotgun = 0,
        bazooka = 1,
        grenade = 2,
        cheesebomb = 3,
        mousetrap = 4   };

#define GREEN                   0x95C355
#define BLUE                    0x3885E7
#define YELLOW                  0XFFFF33
#define MICE_WIDTH              20
#define MICE_HEIGHT             24

#define AMOUNT_OF_CHEESE_HOLES  18
#define RIVER_DIVIDER           7
#define RADIUS_CROSSHAIR        20

#define MOUSE1_IMG              "img/Mouse1(30x37).png"
#define MOUSE_MOVEPOINTS        250
#define MICE_SPEED_MUL          100
#define GRAVITY_MUL             150
#define HILL_OVERCOME_PIXELS    20

// NOTICATIONS' SPECIFICATIONS
#define NOTIFICATION_HP_OFFSET  20
#define NOTIFICATION_HP_WIDTH   25
#define NOTIFICATION_HP_HEIGHT  20
#define NOTIFICATIONBOX_FONTSIZE 20

// WEAPONS' SPECIFICATIONS
#define WEAPON_X_OFFSET         0
#define WEAPON_Y_OFFSET         10
#define WEAPON_WIDTH            20
#define WEAPON_HEIGHT           20

#define SHOTGUN_IMG             "img/Bazooka.png"
#define SHOTGUN_DAMAGE          30
#define SHOTGUN_RANGE           5

#define BAZOOKA_IMG             "img/Bazooka.png"
#define BAZOOKA_DAMAGE          40
#define BAZOOKA_RANGE           40
#define BAZOOKA_WEIGHT          15

#define GRENADE_IMG             "img/Bazooka.png"
#define GRENADE_DAMAGE          30
#define GRENADE_RANGE           40
#define GRENADE_WEIGHT          10
#define GRENADE_TIMER           5

#define CHEESE_IMG              "img/Bazooka.png"
#define CHEESE_DAMAGE           20
#define CHEESE_RANGE            70
#define CHEESE_WEIGHT           15
#define CHEESE_TIMER            5

#define MOUSE_TRAP_IMG          "img/Bazooka.png"
#define MOUSE_TRAP_DAMAGE       30
#define MOUSE_TRAP_RANGE        0
#define MOUSE_TRAP_TRIG_RANGE   5


#endif //MICEWARS_GLOBAL_VARS_H
