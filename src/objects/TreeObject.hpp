#pragma once
# include <glm/glm.hpp>
# include <vector>

#include "VisualServer.h"

class TreeObject {
	std::vector<std::shared_ptr<TreeObject>> childrens;
	TreeObject* parent;
protected:
	glm::mat4 transform;
public:
	TreeObject();
	~TreeObject();
	void Notification(int notification);
	void add_child(std::shared_ptr<TreeObject> node);
	void move(const glm::vec3& move_transform);
	void draw_notification(VisualServer* server) const;
	void process_notification(float delta);
	glm::mat4 get_world_transform() const;
	virtual void process(float delta);
	virtual void draw(VisualServer* server) const;
};








