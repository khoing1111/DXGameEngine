#include "FrameController.h"


GameCore::Frame::FrameController::FrameController()
{
    m_currentFrame = 0;
    m_currentTime = 0;
    m_numFrame = 0;
    m_timePerFrame = 0;
}

GameCore::Frame::FrameController::FrameController(const FrameController& clone)
{
    m_currentTime = clone.m_currentTime;
    m_currentFrame = clone.m_currentFrame;
    m_numFrame = clone.m_numFrame;
    m_timePerFrame = clone.m_numFrame;
}

GameCore::Frame::FrameController::~FrameController()
{

}

void GameCore::Frame::FrameController::SetTimePerFrame(float tpf)
{
    m_timePerFrame = tpf;
    if (m_timePerFrame < 0)
        m_timePerFrame = 0;
}

void GameCore::Frame::FrameController::Advance(float time)
{
    if (m_timePerFrame <= 0)
        return;

    // Update frame timer
    m_currentTime += time;

    // Timer cannot go bellow 0
    if (m_currentTime < 0)
        m_currentTime = 0;

    // Calculate frame
    m_currentFrame = m_currentTime / m_timePerFrame;

    if (m_currentFrame < 0)
    {
        m_currentFrame = 0;
        m_currentTime = 0;
    }

    while (m_currentFrame >= m_numFrame)
    {
        m_currentFrame -= m_numFrame;
        m_currentTime -= m_timePerFrame * m_numFrame;
    }
}

void GameCore::Frame::FrameController::ResetCounter()
{
    m_currentFrame = 0;
    m_currentTime = 0;
}

void GameCore::Frame::FrameController::SetNumFrame(uint numFrame)
{
    m_numFrame = numFrame;
}

uint GameCore::Frame::FrameController::GetNumFrame()
{
    return m_numFrame;
}

uint GameCore::Frame::FrameController::GetCurrentFrame()
{
    return m_currentFrame;
}