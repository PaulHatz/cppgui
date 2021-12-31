#include "main.h"

void incrButton_Click(guiObject *obj, EventArgs *e)
{
	auto numericUpDown = (NumericUpDown *)obj->getParent();
	numericUpDown->setTextOffset(0);

	if(numericUpDown->value + numericUpDown->incr <= numericUpDown->max)
		numericUpDown->value += numericUpDown->incr;

	numericUpDown->setText(std::to_string(numericUpDown->value));
}

void decrButton_Click(guiObject *obj, EventArgs *e)
{
	auto numericUpDown = (NumericUpDown *)obj->getParent();
	numericUpDown->setTextOffset(0);

	if (numericUpDown->value - numericUpDown->incr >= numericUpDown->min)
		numericUpDown->value -= numericUpDown->incr;

	numericUpDown->setText(std::to_string(numericUpDown->value));
}

void NumericUpDown::updateGuiElements(int time)
{
	this->updateBaseGuiElements(time);

	this->updateChildren();
}

void NumericUpDown::show()
{
	this->bVisible = true;

	this->showBaseElems();

	for (auto child : this->getChildren()) {
		if(child->getObjectType() != ObjectType::OBJ_MenuStrip)
			child->show();
	}
}

void NumericUpDown::hide()
{
	this->bVisible = false;

	this->hideBaseElems();

	for (auto child : this->getChildren()) {
		child->hide();
	}
}

void NumericUpDown::setMinimum(float min)
{
	this->min = min;
}

void NumericUpDown::setMaximum(float max)
{
	this->max = max;
}

void NumericUpDown::setIncrement(float incr)
{
	this->incr = incr;
}

bool NumericUpDown::isCharacterAllowed(UINT key)
{
	if (key >= '0' && key <= '9')
		return true;

	return false;
}

void NumericUpDown::updateValue(std::string newValue)
{
	this->value = float(atof(newValue.c_str()));

	if (this->value > this->max)
		this->value = max;

	if (this->value < min)
		this->value = this->min;

	this->setText(std::to_string(this->value));
}

void NumericUpDown::processCustomizedInputCustom(UINT key)
{
	switch (key) {
	case KEYPRESS_UP:
	{
		this->setTextOffset(0);

		if (this->value + this->incr <= this->max)
			this->value += this->incr;

		this->setText(std::to_string(this->value));

		break;
	}
	case KEYPRESS_DOWN: {
		this->setTextOffset(0);

		if (this->value - this->incr >= this->min)
			this->value -= this->incr;

		this->setText(std::to_string(this->value));
		break;
	}

	default:break;
	}
}

NumericUpDown::NumericUpDown(guiObject *parent) : TextInput(parent, ObjectType::OBJ_NumericUpDown)
{
	this->min = 0.f;
	this->max = 100.f;
	this->incr = 1.f;
	this->value = 5.f;
	
	this->setPosition(460, 290);
	this->setSize(120, 25.f);
	this->setFontSize(12.f);

	this->setText(std::to_string(this->value));

	this->incrButton = new Button(this);
	this->incrButton->setText("^");
	this->incrButton->setSize(20, this->getHeight()/2);
	this->incrButton->setPosition(this->getX() + this->getWidth() - this->incrButton->getWidth(), this->getY());
	this->incrButton->addEvent(eventClick, incrButton_Click);


	this->decrButton = new Button(this);
	this->decrButton->setText("v");
	this->decrButton->setSize(20, this->getHeight() / 2);
	this->decrButton->setPosition(this->getX() + this->getWidth() - this->incrButton->getWidth(), this->getY() + (this->getHeight() / 2.f));
	this->decrButton->addEvent(eventClick, decrButton_Click);
}