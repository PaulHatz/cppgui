#include "main.h"

void tpHitBox_Hover(guiObject *sender, EventArgs *e)
{
	auto tabPage = (TabPage *)e->ptr;

	tabPage->hitboxText->FadeOverTime(250, 47, 128, 237, 255);
}

void tpHitBox_Unhover(guiObject *sender, EventArgs *e)
{
	auto tabPage = (TabPage *)e->ptr;

	tabPage->hitboxText->FadeOverTime(250, 255, 255, 255, 255);
}


float TabPage::getHitboxWidth()
{
	return getStringWidth(this->text, 12.f, 0) + 12.f;
}

void TabPage::setText(std::string text)
{
	auto tabControl = (TabControl *)this->getParent();

	this->text = text;

	if(this->hitboxText)
		this->hitboxText->ChangeText(this->text);

	this->hitBox->setSize(this->getHitboxWidth(), 20);

	tabControl->updateGuiElements(0);
}

std::string TabPage::getText()
{
	return this->text;
}

void TabPage::setIndex(int index)
{
	this->index = index;
}

int TabPage::getIndex()
{
	return this->index;
}

void TabPage::updateGuiElements(int time)
{
	if (this->backgroundElem)
		this->backgroundElem->MoveOverTime(time, this->getX(), this->getY());

	auto x = this->getParent()->getX();
	auto tc = (TabControl *)this->getParent();
	
	if (this->index > 0) {
		for (unsigned int i = 0; i < index; i++) {
			x += tc->getTabPages()[i]->getHitboxWidth();
		}
	}
	auto y = this->getParent()->getY();

	if (this->hitboxBackground) {
		this->hitboxBackground->ScaleOverTime(time, this->hitBox->getWidth(), 2.f);
		this->hitboxBackground->MoveOverTime(time, x, y + 19.f);
	}

	if (this->hitboxText)
		this->hitboxText->MoveOverTime(time, x + 6.f, y + 2.f);


	this->updateChildren();
}

void TabPage::hide()
{
	this->bVisible = false;

	int time = 0;
	this->backgroundElem->FadeOverTime(time, 0, 0, 0, 0);
	this->hitboxBackground->FadeOverTime(time, 47, 128, 237, 0);
	this->hitboxText->FadeOverTime(time, 255, 255, 255, 0);

	for (auto child : this->getChildren()) {
		child->hide();
	}
}

void TabPage::tabChange_HideGuiElements(int time)
{
	time = 0;
	this->backgroundElem->FadeOverTime(time, 0, 0, 0, 0);
	this->hitboxBackground->FadeOverTime(time, 47, 128, 237, 0);

	for (auto child : this->getChildren()) {
		child->hide();
	}
}

void TabPage::show()
{
	this->bVisible = true;

	int time = 0;
	this->hitboxText->FadeOverTime(time, 255, 255, 255, 255);

	if (auto tc = (TabControl *)this->getParent()) {
				
		if (tc->getActiveTabPage() == this) {
			this->backgroundElem->FadeOverTime(time, 0, 0, 0, 255);

			this->hitboxBackground->FadeOverTime(time, 47, 128, 237, 255);

			for (auto child : this->getChildren()) {
				child->show();
			}
		}
	}
}

TabPage::TabPage(guiObject *parent, guiObject *hitBox, unsigned int index) : guiObject(parent, ObjectType::OBJ_TabPage)
{
	if (parent != nullptr)
		parent->addChild(this);

	TabControl *tc = (TabControl *)parent;

	this->hitBox = hitBox;

	this->backgroundElem = new game_hudelem_s();
	this->hitboxBackground = new game_hudelem_s();
	this->hitboxText = new game_hudelem_s();

	this->setPosition(parent->getX() + 1.f, parent->getY() + 31.f);
	this->setSize(parent->getWidth() - 2.f, parent->getHeight() - 32.f);

	this->index = index;

	this->text = "tabpage" + std::to_string(this->index + 1);
	float textWidth = getStringWidth(this->text, 12.f, 0);

	float x = parent->getX();

	if (index > 0) {
		for (unsigned int i = 0; i < index; i++) {
			x += tc->getTabPages()[i]->getHitboxWidth();
		}
	}

	float y = parent->getY();

	this->hitBox->setPosition(x, y);
	this->hitBox->setSize(this->getHitboxWidth(), 20);


	this->hitboxBackground->SetShader(x, y + 19.f, this->hitBox->getWidth(), 2.f, 47, 128, 237, 0);

	this->hitboxText->SetText(this->text,
		x + 6.f,
		y + 2.f, 0, 12.f, false, false, false, 255, 255, 255, 255);

	this->backgroundElem->SetShader(this->getX(), this->getY(), this->getWidth(), this->getHeight(), 0, 0, 0, 0);

	EventArgs *e = new EventArgs;
	e->ptr = this;

	this->hitBox->addEvent(eventHover, std::bind(tpHitBox_Hover, hitBox, e));
	this->hitBox->addEvent(eventUnhover, std::bind(tpHitBox_Unhover, hitBox, e));

}
