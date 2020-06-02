#include "BVH/BVHTree.h"
#include "Utils/Timer.h"

#define PRINT_BUILD_TIME 1

BVHTree::BVHTree(TriangleList* objectList, ctpl::ThreadPool* pool)
	: m_ObjectList(objectList), m_ThreadPool(pool)
{
	m_PoolPtr.store(0);
	reset();
}

void BVHTree::constructBVH()
{
	if (this->m_ObjectList != nullptr)
	{
		buildBVH(&m_ObjectList->m_AABBs);
		return;
	}
}

void BVHTree::buildBVH(std::vector<AABB>* aabbs)
{
	m_ThreadLimitReached = false;
	m_BuildingThreads = 0;

	if (m_PrimitiveCount > 0)
	{
#if PRINT_BUILD_TIME
		utils::Timer t;
		t.reset();
#endif
		m_PoolPtr = 2;
		m_BVHPool.push_back({});
		m_BVHPool.push_back({});

		auto& rootNode = m_BVHPool[0];
		rootNode.bounds.leftFirst = 0;
		rootNode.bounds.count = static_cast<int>(m_PrimitiveCount);
		rootNode.CalculateBounds(aabbs->data(), m_PrimitiveIndices.data());

		//if (m_ThreadPool != nullptr)
			//rootNode.SubdivideMT(aabbs->data(), m_BVHPool.data(), m_PrimitiveIndices.data(), m_ThreadPool, &m_ThreadMutex, &m_PoolPtrMutex, &m_BuildingThreads, 1, m_PoolPtr);
		//else
			rootNode.Subdivide(aabbs->data(), m_BVHPool.data(), m_PrimitiveIndices.data(), 1, m_PoolPtr);

		if (m_PoolPtr > 2)
			rootNode.bounds.count = -1, rootNode.SetLeftFirst(2);
		else
			rootNode.bounds.count = static_cast<int>(m_PrimitiveCount);

		m_BVHPool.resize(m_PoolPtr);
#if PRINT_BUILD_TIME
		std::cout << "Building BVH use: " << t.elapsed() << " ms " << std::endl;
#endif
		CanUseBVH = true;
	}
}

void BVHTree::reset()
{
	CanUseBVH = false;
	m_BVHPool.clear();

	m_PrimitiveCount = m_ObjectList->getPrimCount();
	if (m_PrimitiveCount > 0)
	{
		m_PrimitiveIndices.clear();
		for (int i = 0; i < m_PrimitiveCount; i++)
			m_PrimitiveIndices.push_back(i);
		m_BVHPool.resize(m_PrimitiveCount * 2);
	}
}