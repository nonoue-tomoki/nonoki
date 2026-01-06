#include "Field.h"

Field::Field():Base(eType_Field){
	m_img = COPY_RESOURCE("Background", CImage);

	m_img.SetSize(1920, 1080);
}

void Field::Draw() {
	m_img.Draw();
}

