#pragma once

#include "TreeObject.hpp"

class Mesh: public TreeObject {
	void draw_self(VisualServer* server) const override;
};