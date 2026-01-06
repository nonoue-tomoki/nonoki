#include "Field.h"

Field::Field():Base(eType_Field){
	m_img = COPY_RESOURCE("Background", CImage);
}

void Field::Draw() {
	m_img.Draw();
}

