#include "BVH/MBVHTree.h"

#define PRINT_BUILD_TIME 1

#if PRINT_BUILD_TIME
#include "Utils/Timer.h"
#endif

MBVHTree::MBVHTree(BVHTree *orgTree)
{
	this->m_PrimitiveIndices = orgTree->m_PrimitiveIndices;
	this->m_OriginalTree = orgTree;
}

void MBVHTree::constructBVH()
{
	m_Tree.clear();
	m_Tree.resize(m_OriginalTree->m_PrimitiveCount * 2);
	if (this->m_OriginalTree->m_ObjectList->m_AABBs.size() > 0)
	{
		utils::Timer t{};
		m_FinalPtr = 1;
		MBVHNode &mRootNode = m_Tree[0];
		BVHNode &curNode = m_OriginalTree->m_BVHPool[0];
		mRootNode.MergeNodes(curNode, this->m_OriginalTree->m_BVHPool, this);

		std::cout << "Translate BVH to GPU use " << t.elapsed() << " ms" << std::endl;
		m_CanUseBVH = true;
	}
}