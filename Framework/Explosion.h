#pragma once

#ifndef ___EXPLOSION_H___
#define ___EXPLOSION_H___

class AnimatedSprite;
class BackBuffer;

class Explosion
{
public:
	Explosion();
	~Explosion();

	void Process(float deltaTime);
	bool Initialise(AnimatedSprite* sprite);
	void Draw(BackBuffer& backBuffer);
	
	void SetDead(bool dead);
	bool IsDead() const;

	void SetPosition(float x, float y);
	void SetPositionX(float x);
	void SetPositionY(float y);
	void SetFrameSize(int w, int h);
	void SetAnimationSpeed(float s);

	float GetPositionX() const;
	float GetPositionY() const;

	static const int NUMBER_OF_FRAMES = 4;

protected:
	AnimatedSprite* m_pAnimatedSprite;

	float m_x;
	float m_y;
	bool m_dead;

};

#endif // ___EXPLOSION_H___