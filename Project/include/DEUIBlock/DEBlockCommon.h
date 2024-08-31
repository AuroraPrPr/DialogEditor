#ifndef DEBLOCKCOMMON_H
#define DEBLOCKCOMMON_H

#include "DEBlockContainer.h"
#include "DEBlockAngularDimension.h"
#include "DEBlockDimension.h"
#include "DEBlockDouble.h"
#include "DEBlockEnumeration.h"
#include "DEBlockGroup.h"
#include "DEBlockInt.h"
#include "DEBlockLabel.h"
#include "DEBlockLinearDimension.h"
#include "DEBlockObject.h"
#include "DEBlockRadiusDimension.h"
#include "DEBlockToggle.h"

DEUIBLOCK_EXPORT DEBlock* CreateBlock(QWidget* pParent, QString type, QString blockID, QString label);

DEUIBLOCK_EXPORT void AddBlockToContainer(DEBlockContainer* pContainer, DEBlock* pBlock);
DEUIBLOCK_EXPORT void AddBlockToContainer(DEBlockContainer* pContainer, DEBlock* pBlock, int row, int column);

DEUIBLOCK_EXPORT void AddLayoutToContainer(DEBlockContainer* pContainer, DEBlockLayoutBase* pBlock);
DEUIBLOCK_EXPORT void AddLayoutToContainer(DEBlockContainer* pContainer, DEBlockLayoutBase* pBlock, int row, int column);

DEUIBLOCK_EXPORT void AddBlockToLayout(DEBlockContainer* pContainer, DEBlockLayoutBase* pLayout, DEBlock* pBlock);
DEUIBLOCK_EXPORT void AddBlockToLayout(DEBlockContainer* pContainer, DEBlockLayoutBase* pLayout, DEBlock* pBlock, int row, int column);

DEUIBLOCK_EXPORT void AddLayoutToLayout(DEBlockContainer* pContainer, DEBlockLayoutBase* pLayout, DEBlockLayoutBase* pBlock);
DEUIBLOCK_EXPORT void AddLayoutToLayout(DEBlockContainer* pContainer, DEBlockLayoutBase* pLayout, DEBlockLayoutBase* pBlock, int row, int column);

#endif // DEBLOCKCOMMON_H
