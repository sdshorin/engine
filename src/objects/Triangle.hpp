#pragma once

#include "TreeObject.hpp"

class Triangle: public TreeObject {
	void draw(VisualServer* server) const override;
};