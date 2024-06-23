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
        Bullet/SnowPea.cpp
        Bullet/SnowPea.hpp
        Bullet/Mower.hpp
        Bullet/Mower.cpp

        // UI
        UI/Component/Image.cpp
        UI/Component/Image.hpp
        UI/Component/ImageButton.cpp
        UI/Component/ImageButton.hpp
        UI/Component/Label.cpp
        UI/Component/Label.hpp
        UI/Component/Slider.cpp
        UI/Component/Slider.hpp
        UI/Animation/PlantAnimation.cpp
        UI/Animation/PlantAnimation.hpp
        UI/Animation/ZombieAnimation.hpp
        UI/Animation/ZombieAnimation.cpp

        // Zombie
        Zombie/Zombie.cpp
        Zombie/Zombie.hpp
        Zombie/BasicZombie.cpp
        Zombie/BasicZombie.hpp
        Zombie/FootballZombie.cpp
        Zombie/FootballZombie.hpp
        Zombie/NewspaperZombie.cpp
        Zombie/NewspaperZombie.hpp
        Zombie/ConeZombie.cpp
        Zombie/ConeZombie.hpp
        Zombie/FlagZombie.cpp
        Zombie/FlagZombie.hpp
        Zombie/BucketZombie.cpp
        Zombie/BucketZombie.hpp

        // Plant
        Plant/Plant.cpp
        Plant/Plant.hpp
        Plant/Peashooter.cpp
        Plant/Peashooter.hpp
        Plant/Repeater.cpp
        Plant/Repeater.hpp
        Plant/SnowPeashooter.cpp
        Plant/SnowPeashooter.hpp
        Plant/GatlinPeashooter.cpp
        Plant/GatlinPeashooter.hpp
        Plant/Sunflower.cpp
        Plant/Sunflower.hpp
        Plant/Sun.cpp
        Plant/Sun.hpp
        Plant/TwinSunflower.cpp
        Plant/TwinSunflower.hpp
        Plant/Wallnut.cpp
        Plant/Wallnut.hpp
        Plant/Shovel.cpp
        Plant/Shovel.hpp
        Plant/LawnMower.hpp
        Plant/LawnMower.cpp
        Plant/CherryBomb.cpp
        Plant/CherryBomb.hpp
        Plant/PlantButton.cpp
        Plant/PlantButton.hpp

        // Scene
        Scene/PlayScene.cpp
        Scene/PlayScene.hpp
        Scene/MenuScene.cpp
        Scene/MenuScene.hpp
        Scene/StartScene.cpp
        Scene/StartScene.hpp

        main.cpp
        Bullet/BowlingBall.cpp
        Bullet/BowlingBall.hpp
        Plant/Bombnut.cpp
        Plant/Bombnut.hpp
        Bullet/BombBowlingBall.cpp
        Bullet/BombBowlingBall.hpp
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