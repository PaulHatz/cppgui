#include "main.h"

void TrackBar_Click(guiObject *obj, EventArgs *e)
{
	auto trackBar = (TrackBar *)obj;

	float delta = guiApplication->getCursorInfo()->cursorPosition[0] - trackBar->getX();

	float w = (trackBar->maxValue - trackBar->minValue);

	trackBar->setValue((delta / trackBar->getWidth()) * w);
}

void TrackBar_Drag(guiObject *obj, EventArgs *e)
{
	auto trackBar = obj->getObjectType() == ObjectType::OBJ_TrackBar ? (TrackBar *)obj : (TrackBar *)obj->getParent();

	float delta = guiApplication->getCursorInfo()->cursorPosition[0] - trackBar->getX();

	float w = (trackBar->maxValue - trackBar->minValue);

	trackBar->setValue((delta / trackBar->getWidth()) * w);	
}

void TrackBar::show()
{
	if(this->lineElem)
		this->lineElem->FadeOverTime(0, 255.f, 255.f, 255.f, 255.f);
	
	if(this->selectorElem)
		this->selectorElem->FadeOverTime(0, 47.f, 128.f, 237.f, 255.f);

	this->bVisible = true;
}

void TrackBar::hide()
{
	if (this->lineElem)
		this->lineElem->FadeOverTime(0, 255.f, 255.f, 255.f, 0);

	if (this->selectorElem)
		this->selectorElem->FadeOverTime(0, 47.f, 128.f, 237.f, 0);

	this->bVisible = false;
}

void TrackBar::updateGuiElements(int time)
{
	if (this->lineElem) {
		this->lineElem->MoveOverTime(time, this->getX(), this->getY() + 8.f);
		this->lineElem->ScaleOverTime(time, this->getWidth(), 2.f);
	}

	if (this->selectorElem) {
		auto child = this->getChildren().front();
		this->selectorElem->MoveOverTime(time, child->getX(), child->getY() + 8.f);
	}
}

void TrackBar::setMinimum(float value)
{
	this->minValue = value;

	if (this->value < value)
		this->setValue(value);

}

void TrackBar::setMaximum(float value)
{
	this->maxValue = value;

	if (this->value > value)
		this->setValue(value);
}

void TrackBar::setValue(float value)
{
	if (value <= this->maxValue && value >= this->minValue) {
		this->value = value;
		this->getChildren().front()->setPosition(this->getX() + (this->getWidth() * (this->value / (this->maxValue - this->minValue))) - 2.f, this->getY() - 7.f);
	}
	else {
		if (value < this->minValue) {
			this->value = 0;
			this->getChildren().front()->setPosition(this->getX() + (this->getWidth() * (this->value / (this->maxValue - this->minValue))) - 2.f, this->getY() - 7.f);
			updateGuiElements(0);
		}
		else if (value > this->maxValue) {
			this->value = this->maxValue;
			this->getChildren().front()->setPosition(this->getX() + (this->getWidth() * (this->value / (this->maxValue - this->minValue))) - 2.f, this->getY() - 7.f);
			updateGuiElements(0);
		}
	}

	updateGuiElements(0);
	guiApplication->sendEvent(eventValueChanged, this);
}

TrackBar::TrackBar(guiObject *parent) : guiObject(parent, ObjectType::OBJ_TrackBar)
{
	if (parent) {
		parent->addChild(this);
		this->setEnabled(parent->Enabled());
	}

	this->lineElem = new game_hudelem_s();
	this->selectorElem = new game_hudelem_s();

	this->value = 0.f;
	this->minValue = 0.f;
	this->maxValue = 100.f;


	guiObject *obj = new guiObject(this);
	obj->setPosition(this->getX() - 2.f, this->getY() - 7.f);
	obj->setSize(5.f, 15.f);
	obj->addEvent(eventDrag, TrackBar_Drag);
	this->addChild(obj);

	this->setSize(150.f, 15.f);


	if (this->lineElem)
		this->lineElem->SetShader(this->getX(), this->getY() + 8.f, 0.f, 0.f, 255.f, 255.f, 255.f, this->Enabled() ? 255.f : 0.f);

	if(this->selectorElem)
		this->selectorElem->SetShader(this->getX(), obj->getY(), 5.f, 15.f, 47.f, 128.f, 237.f, this->Enabled() ? 255.f : 0.f);

	this->addEvent(eventClick, TrackBar_Click);
	this->addEvent(eventDrag, TrackBar_Drag);
}
