#pragma once
class Pause {
	CImage m_img;
	CImage m_button;
	int m_sw;
	static Pause* m_instance;
	static Pause* GetInstance() {
		return m_instance;
	}
	Pause();
	~Pause();
	bool ColButton(const CImage& m, const CVector2D& pos);
	void Draw();
public:
	static bool Update();
};