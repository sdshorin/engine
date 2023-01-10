#pragma once

#include "TreeObject.hpp"

class Triangle: public TreeObject {
	void draw_self(VisualServer* server) const override;
};