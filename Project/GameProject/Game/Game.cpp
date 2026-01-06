#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Goal.h"
#include "Map.h"
#include "Field.h"
#include "../Screen/Result.h"
#include "../Screen/Title.h"

int Game::s_next_area_id = 11;
CVector2D Game::s_next_pos = CVector2D(SPAWN_X_LEFT, SPAWN_Y_BOTTOM);

int Game::s_current_area_id = 11;
CVector2D Game::s_restart_pos = CVector2D(SPAWN_X_LEFT, SPAWN_Y_BOTTOM);


void Game::LoadArea(int area_id, const CVector2D& player_pos)
{
    Base::Add(new Map(area_id));
    Base::Add(new Field);
    Base::Add(new Player(player_pos, false));

    s_current_area_id = area_id;
    s_restart_pos = player_pos;

    if (area_id == 11) {
        // —á: Base::Add(new Enemy(...));
    }
}

void Game::Update()
{
    m_time++;

    Player* p = dynamic_cast<Player*>(Base::FindObject(eType_Player));

    if (p && p->GetNextAreaFlag()) {
        s_next_area_id = p->GetNextAreaID();
        s_next_pos = p->GetNextPos();

        for (auto& obj : m_list) {
            if (obj != this) {
                obj->m_kill = true;
            }
        }
        LoadArea(s_next_area_id, s_next_pos);
        return;
    }

    if (p == NULL) {
        if (PUSH(CInput::eButton3)) {
            m_deathcount++;

            KillAll();

            s_next_area_id = s_current_area_id;
            s_next_pos = s_restart_pos;

            Base::Add(new Game());
        }
    }
}

Game::Game() :Base(eType_UI)
{
    LoadArea(s_next_area_id, s_next_pos);
}

