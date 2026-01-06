#pragma once
#include "Base/Base.h"
#include "Map.h"

#define DASH_SPEED 10
#define WALL_SLIDE_SPEED 1
#define MOVE_SPEED 4
#define JUMP_POWER 10
#define WALL_KICK_POWER_X 10
#define WALL_KICK_POWER_Y 12

#define GROUND_FRICTION 0.80f
#define ICE_FRICTION    0.98f

#define SPRING_POWER 16

class Player : public Base {
private:
    enum {
        eAnimIdle = 0,
        eAnimRun,
        eAnimJumpUp,
        eAnimJumpDown,
        eAnimDown,
    };

    enum {
        eState_Idle,
        eState_Jump,
        eState_WallGrab,
        eState_Down,
    };
    int m_state;
    Map* m_map = nullptr;
    bool m_touch_wall = false;

    CImage m_img;
    bool m_flip;
    bool m_is_ground;
    int m_wall_dir;
    int m_jump_count;
    const static int MAX_JUMP = 2;
    bool m_can_dash;
    int m_dash_keep = 0;

    int m_ground_tile = TILE_SOLID;

    bool m_next_area = false;
    int m_next_area_id = 0;
    CVector2D m_next_pos;

    void PlayerDash();

public:
    Player(const CVector2D& pos, bool flip);
    ~Player() override;

    void Update() override;
    void Draw() override;
    void Collision(Base* b) override;

    void StateIdle();
    void StateJump();
    void StateWallGrab();
    void StateDown();

    bool GetNextAreaFlag() const {
        return m_next_area;
    }
    int GetNextAreaID() const {
        return m_next_area_id;
    }
    const CVector2D& GetNextPos() const {
        return m_next_pos;
    }
};
