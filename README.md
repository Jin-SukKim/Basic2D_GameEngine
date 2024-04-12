"# GameEngine" - using C++ & WinAPI

Basic 2D Game Engine

2D Game Engine 프로젝트입니다.

EditScene에서 직접 사용할 Asset을 그려 저장/사용 할 수 있습니다.

Actor와 Component의 조합으로 게임 오브젝트를 생성해 사용할 수 있습니다.

Asset은 현재는 bmp응 이용해 texture, sprite, flipbook을 생성해 사용하고 있으며
충돌은 Collider Component를 이용해 처리합니다.

주요 기능들은 Manager 클래스들이 종합적으로 처리하고 있습니다.


![결과물1](https://github.com/Jin-SukKim/GameEngine/assets/32403432/14b9774c-97d8-4808-bc9f-edf9b020d60f)


This is basic 2D Game Engine project.

Using Editscene, programmer can create and use as game object.

Game object is created by using Actor and Component combination.

Currently assets can be loaded and used only with bmp format images.
Texture, Sprite, and Flipbook are created by using bmp assets.

Collision can be used with Collider components.

Manager classes handle main features for engine such as input, collision check, and etc.
