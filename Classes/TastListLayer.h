#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class TastListLayer:public CCLayer,public CCTableViewDataSource,public CCTableViewDelegate
{
public:
	CREATE_FUNC(TastListLayer);
	bool init();
	void scrollViewDidScroll(CCScrollView* view){}
	void scrollViewDidZoom(CCScrollView* view){}
	void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
	CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
	CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
	unsigned int numberOfCellsInTableView(CCTableView *table);
private:
	CCNode* getItemNode(int i);
	bool isTouched[5];
	int randsum;
};
