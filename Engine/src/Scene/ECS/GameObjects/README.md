# GameObjects

Provided are a list of helping game objects that the engine supports. They are all super generic for different levels of functionality. This entire folder
will absolutely be a complete mess, there is no avoiding it. However, the Engine.h will include everything needed. All GameObjects are a branching tree 
(who would of thought thats OOP) that originate from 1 of 2 options. The 2 very basic objects allowed are GameObject2D and GameObject3D, which provide the
2D and 3D transforms. GameObject is not instantiable, but I guess feel free to make it so if you really need an object that has absolutely 0 data on it.