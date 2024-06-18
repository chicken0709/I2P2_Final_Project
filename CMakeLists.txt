cmake_minimum_required(VERSION 3.27)
project(2024_I2P2_Final_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Resource)

file(COPY Resource/audios DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource/fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource/images DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY allegro_monolith-5.2.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(2024_I2P2_Final_Project
        // Engine
        Engine/Allegro5Exception.cpp
        Engine/Allegro5Exception.hpp
        Engine/AudioHelper.cpp
        Engine/AudioHelper.hpp
        Engine/Collider.cpp
        Engine/Collider.hpp
        Engine/GameEngine.cpp
        Engine/GameEngine.hpp
        Engine/Group.cpp
        Engine/Group.hpp
        Engine/IControl.cpp
        Engine/IControl.hpp
        Engine/IObject.cpp
        Engine/IObject.hpp
        Engine/IScene.cpp
        Engine/IScene.hpp
        Engine/LOG.cpp
        Engine/LOG.hpp
        Engine/Point.cpp
        Engine/Point.hpp
        Engine/Resources.cpp
        Engine/Resources.hpp
        Engine/Sprite.cpp
        Engine/Sprite.hpp

        // Bullet
        Bullet/Bullet.cpp
        Bullet/Bullet.hpp
        Bullet/BasicPea.cpp
        Bullet/BasicPea.hpp

        // UI
        UI/Animation/DirtyEffect.cpp
        UI/Animation/DirtyEffect.hpp
        UI/Animation/ExplosionEffect.cpp
        UI/Animation/ExplosionEffect.hpp
        UI/Component/Image.cpp
        UI/Component/Image.hpp
        UI/Component/ImageButton.cpp
        UI/Component/ImageButton.hpp
        UI/Component/Label.cpp
        UI/Component/Label.hpp
        UI/Component/TextInput.cpp
        UI/Component/TextInput.hpp
        UI/Component/Slider.cpp
        UI/Component/Slider.hpp

        // Zombie
        Zombie/Zombie.cpp
        Zombie/Zombie.hpp
        Zombie/PlaneEnemy.cpp
        Zombie/PlaneEnemy.hpp
        Zombie/TankEnemy.cpp
        Zombie/TankEnemy.hpp
        Zombie/TankEnemy2.cpp
        Zombie/TankEnemy2.hpp
        Zombie/BasicZombie.cpp
        Zombie/BasicZombie.hpp

        // Plant
        Plant/Peashooter.cpp
        Plant/Peashooter.hpp
        Plant/Plant.cpp
        Plant/Plant.hpp
        Plant/PlantButton.cpp
        Plant/PlantButton.hpp

        // Scene
        Scene/LoseScene.cpp
        Scene/LoseScene.hpp
        Scene/PlayScene.cpp
        Scene/PlayScene.hpp
        Scene/StageSelectScene.cpp
        Scene/StageSelectScene.hpp
        Scene/WinScene.cpp
        Scene/WinScene.hpp
        Scene/StartScene.cpp
        Scene/StartScene.hpp
        Scene/SettingsScene.cpp
        Scene/SettingsScene.hpp

        main.cpp
        Plant/Repeater.cpp
        Plant/Repeater.hpp
        Plant/SnowPeashooter.cpp
        Plant/SnowPeashooter.hpp
        Bullet/SnowPea.cpp
        Bullet/SnowPea.hpp
        Plant/GatlinPeashooter.cpp
        Plant/GatlinPeashooter.hpp
        Plant/Sunflower.cpp
        Plant/Sunflower.hpp
        Plant/Sun.cpp
        Plant/Sun.hpp
        Plant/TwinSunflower.cpp
        Plant/TwinSunflower.hpp
)

IF (WIN32)
    target_include_directories(2024_I2P2_Final_Project PUBLIC C:/allegro/include)
    target_link_directories(2024_I2P2_Final_Project PUBLIC C:/allegro/lib)
    target_compile_options(2024_I2P2_Final_Project PUBLIC ${ALLEGRO5_CFLAGS_OTHER})
    target_link_libraries(2024_I2P2_Final_Project liballegro_monolith)
ELSE()
    find_package(PkgConfig)
    pkg_check_modules(ALLEGRO5 REQUIRED allegro-5 allegro_main-5 allegro_font-5 allegro_dialog-5 allegro_primitives-5 allegro_image-5 allegro_ttf-5 allegro_audio-5 allegro_acodec-5)
    target_include_directories(2024_I2P2_Final_Project PUBLIC lib)
    target_include_directories(2024_I2P2_Final_Project PUBLIC ${ALLEGRO5_INCLUDE_DIRS})
    target_compile_options(2024_I2P2_Final_Project PUBLIC ${ALLEGRO5_CFLAGS_OTHER})
    target_link_libraries(2024_I2P2_Final_Project ${ALLEGRO5_LIBRARIES})
    target_link_directories(2024_I2P2_Final_Project PUBLIC ${ALLEGRO5_LIBRARY_DIRS})
ENDIF()