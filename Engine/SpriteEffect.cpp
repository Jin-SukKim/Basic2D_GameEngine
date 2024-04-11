#include "pch.h"
#include "SpriteEffect.h"
#include "World.h"
#include "Level.h"
#include "AssetManager.h"
#include "Flipbook.h"

SpriteEffect::SpriteEffect()
{
	SetLayer(LayerType::LT_EFFECT);
}

SpriteEffect::~SpriteEffect()
{

}
void SpriteEffect::Init()
{
	Super::Init();

	UpdateAnimation();
}

void SpriteEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

 	if (IsAnimationEnded()) {
		std::shared_ptr<Level> level = World::GetCurrentLevel();
		if (level)
			level->RemoveActor(weak_from_this());
		Reset();
	}
}

void SpriteEffect::Render(HDC hdc)
{
	Super::Render(hdc);
}

void SpriteEffect::UpdateAnimation()
{
	SetFlipbook(GET_SINGLE(AssetManager)->GetFlipbook(GetFlipbook()->GetInfo().name));
}
