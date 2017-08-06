// This includes:
#include "animatedsprite.h"

// Local includes:
#include "texture.h"
#include "texture.h"
#include "Explosion.h"
#include "backbuffer.h"

AnimatedSprite::AnimatedSprite()
: m_frameSpeed(0)
, m_frameWidth(0)
, m_frameHeight(0)
, m_timeElapsed(0.0f)
, m_currentFrame(0)
, m_paused(false)
, m_loop(false)
, m_animating(false)
{

}

AnimatedSprite::~AnimatedSprite()
{

}

bool AnimatedSprite::Initialise(Texture& texture)
{
	Sprite::Initialise(texture);

	StartAnimating();

	return true;
}

void AnimatedSprite::AddFrame(int x)
{
	// Add the x coordinate to the frame coordinate container.
	m_xValues.push_back(x);
}

void AnimatedSprite::Process(float deltaTime)
{
	if (!IsPaused())
	{
		// Count the time elapsed.
		m_timeElapsed += deltaTime;

		// If the time elapsed is greater than the frame speed.
		if (m_timeElapsed > m_frameSpeed)
		{
			// Move to the next frame.
			++m_currentFrame;

			// Reset the time elapsed counter.
			m_timeElapsed -= m_frameSpeed;
		}

		// W03.4: If the current frame is greater than the number of frame in this animation...
		if (m_currentFrame > Explosion::NUMBER_OF_FRAMES)
		{
			// Reset to the first frame if looping.
			m_currentFrame = 0;

			// Stop the animation if it is not looping...
			if (!IsLooping())
			{
				m_animating = false;
			}
		}
	}
}

void AnimatedSprite::Draw(BackBuffer& backbuffer)
{
	// Draw the particular frame into the backbuffer.
	backbuffer.DrawAnimatedSprite(*this);
}

void AnimatedSprite::SetFrameSpeed(float f)
{
	m_frameSpeed = f;
}

void AnimatedSprite::SetFrameWidth(int w)
{
	m_frameWidth = w;
}

void AnimatedSprite::SetFrameHeight(int h)
{
	m_frameHeight = h;
}

void AnimatedSprite::Pause()
{
	m_paused = !m_paused;
}

bool AnimatedSprite::IsPaused()
{
	return m_paused;
}

bool AnimatedSprite::IsAnimating()
{
	return m_animating;
}

void AnimatedSprite::StartAnimating()
{
	m_animating = true;

	m_timeElapsed = 0;
	m_currentFrame = 0;
}

bool AnimatedSprite::IsLooping()
{
	return m_loop;
}

void AnimatedSprite::SetLooping(bool b)
{
	m_loop = b;
}

int AnimatedSprite::GetFrameWidth()
{
	return m_frameWidth;
}

int AnimatedSprite::GetFrameHeight()
{
	return m_frameHeight;
}

int AnimatedSprite::GetCurrentFrame()
{
	return m_currentFrame;
}
