#ifndef CATEGORY_H
#define CATEGORY_H

namespace Category
{
    enum Type
    {
        None      = 0,
        Scene     = 1 << 0,
        PlayerCar = 1 << 1,
        AlliedCar = 1 << 2,
        EnemyCar  = 1 << 3,

        Button    = 1 << 4
    };

    unsigned int AnyCar = PlayerCar 
                        | AlliedCar 
                        | EnemyCar;
}

#endif