#include "main.h"

void TabControl_Click(guiObject *sender, TabChangeEventArgs *e)
{
	TabControl *tabControl = (TabControl *)sender->getParent();

	if (tabControl != nullptr && e->tabpagePtr != nullptr)
		tabControl->changeTabPage(e->tabpagePtr);
}

void TabControl::updateGuiElements(int time)
{
	float x = this->getX(), y = this->getY(),
		width = this->getWidth(), height = this->getHeight();

	if(this->backgroundElem)
		this->backgroundElem->MoveOverTime(time, x, y + 30.f);

	if (this->backgroundElem)
		this->backgroundElem->ScaleOverTime(time, this->getWidth(), this->getHeight() - 30.f);

	
	for (auto page : this->pages) {
		if (page->getObjectType() == ObjectType::OBJ_TabPage) {
			page->setPosition(x + 1.f, y + 31.f);
			page->setSize(width - 2.f, height - 32.f);
		}
	}

	this->updateChildren();
}

void TabControl::setEnabled(bool value)
{
	for (auto child : this->getChildren()) {

		if (value) {
			if (child->getObjectType() != ObjectType::OBJ_TabPage)
				child->setEnabled(true);

			else if (child->getObjectType() == ObjectType::OBJ_TabPage && child == this->activeTabPage)
				child->setEnabled(true);

			else if (child->getObjectType() == ObjectType::OBJ_TabPage && child != this->activeTabPage)
				child->setEnabled(false);

		}
		else child->setEnabled(false);
	}
}

void TabControl::show()
{
	this->bVisible = true;

	int time = 0;

	if (this->backgroundElem)
		this->backgroundElem->FadeOverTime(time, 47, 128, 237, 255);

	for (auto child : this->getChildren()) {
		child->show();

		if (child->getObjectType() == ObjectType::OBJ_TabPage && child != this->activeTabPage)
			child->setEnabled(false);

	}
}

void TabControl::hide()
{
	this->bVisible = false;

	int time = 0;

	if (this->backgroundElem)
		this->backgroundElem->FadeOverTime(time, 47, 128, 237, 0);

	for (auto child : this->getChildren()) {
		child->hide();
	}
}


std::vector<TabPage *> TabControl::getTabPages()
{
	return this->pages;
}

void TabControl::changeTabPage(TabPage *newPage)
{
	if (this->activeTabPage != nullptr) {
		if (this->activeTabPage == newPage)
			return;

		this->activeTabPage->setEnabled(false);
		this->activeTabPage->tabChange_HideGuiElements(0);
	}

	this->activeTabPage = newPage;
	
	if (this->activeTabPage != nullptr) {
		this->activeTabPage->setEnabled(true);

		this->addChild(newPage);

		this->activeTabPage->show();
	}
}

TabPage *TabControl::getActiveTabPage()
{
	return this->activeTabPage;
}

TabPage *TabControl::addNewTabPage(std::string text)
{
	unsigned int numPages = this->pages.size();

	if ((numPages + 1) < 10) {

		guiObject *tabControlHitBox = new guiObject(this);

		TabPage *tabPage = new TabPage(this, tabControlHitBox, numPages);
		tabPage->setIndex(numPages);
		tabPage->setText(text);
		tabPage->setEnabled(false);

		if (tabPage != nullptr) {
			float x = this->getX();

			this->addChild(tabControlHitBox);

			TabChangeEventArgs *e = new TabChangeEventArgs();
			ZeroMemory(e, sizeof(e));
			e->tabpagePtr = tabPage;

			tabControlHitBox->addEvent(eventClick, std::bind(TabControl_Click, tabControlHitBox, (TabChangeEventArgs *)e));

			this->pages.push_back(tabPage);

			return tabPage;
		}

		return nullptr;

	}
	else printf("Too many tabs\n");
	return nullptr;
}

TabControl::TabControl(guiObject *parent) : guiObject(parent, this)
{
	if (parent)
		parent->addChild(this);

	this->setPosition(300, 200);
	this->setSize(300, 300);

	this->backgroundElem = new game_hudelem_s();

	this->backgroundElem->SetShader(this->getX(), this->getY() + 30.f, this->getWidth(), this->getHeight() - 30.f, 47, 128, 237, 255);

	this->activeTabPage = nullptr;
}
