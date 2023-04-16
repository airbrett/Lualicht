#include "Scene.h"
#include <irrlicht.h>

#include "Helpers.h"

sol::table InitScene(sol::this_state L)
{
	sol::state_view lua(L);
	sol::table scene = lua.create_table();

	scene.new_usertype<irr::scene::IMeshBuffer>(
		"IMeshBuffer", sol::no_constructor,
		"getIndexCount", &irr::scene::IMeshBuffer::getIndexCount,
		"getVertex", [](irr::scene::IMeshBuffer& buf, irr::u32 index) -> irr::video::S3DVertex*
		{
			irr::video::S3DVertex* vtxptr = reinterpret_cast<irr::video::S3DVertex*>(buf.getVertices()) + index;

			switch (buf.getVertexType())
			{
			case irr::video::EVT_STANDARD:
			{
				return reinterpret_cast<irr::video::S3DVertex*>(buf.getVertices()) + index;
				break;
			}
			case irr::video::EVT_2TCOORDS:
				return reinterpret_cast<irr::video::S3DVertex2TCoords*>(vtxptr);
				break;
			case irr::video::EVT_TANGENTS:
				return reinterpret_cast<irr::video::S3DVertexTangents*>(vtxptr);
				break;
			}

			return nullptr;
			//return v;
		},
		"getIndex",
			[](irr::scene::IMeshBuffer& buf, irr::u32 index)
			{
				return buf.getIndices()[index];
			}
		);

	scene.new_usertype<irr::scene::IMesh>(
		"IMesh", sol::no_constructor,
		"getMeshBufferCount", &irr::scene::IMesh::getMeshBufferCount,
		"getMeshBuffer", sol::resolve<irr::scene::IMeshBuffer* (irr::u32) const>(&irr::scene::IMesh::getMeshBuffer)
	);

	scene.new_usertype<irr::scene::IAnimatedMesh>(
		"IAnimatedMesh", sol::no_constructor,
		sol::base_classes, sol::bases<irr::scene::IMesh>()
	);

	scene.new_usertype<irr::scene::ISceneManager>(
		"ISceneManager", sol::no_constructor,
		"drawAll", &irr::scene::ISceneManager::drawAll,
		"addExternalMeshLoader", &irr::scene::ISceneManager::addExternalMeshLoader,
		"getMesh", [](irr::scene::ISceneManager& smgr, const char* filename) { return smgr.getMesh(filename); },
		"addSceneNode", &irr::scene::ISceneManager::addSceneNode,
		"addAnimatedMeshSceneNode", sol::overload(
			[](irr::scene::ISceneManager& smgr, irr::scene::IAnimatedMesh* mesh) { return smgr.addAnimatedMeshSceneNode(mesh); },
			[](irr::scene::ISceneManager& smgr, irr::scene::IAnimatedMesh* mesh, irr::scene::ISceneNode* parent) {
				return smgr.addAnimatedMeshSceneNode(mesh, parent);
			},
			[](irr::scene::ISceneManager& smgr, irr::scene::IAnimatedMesh* mesh, irr::scene::ISceneNode* parent, irr::s32 id) {
				return smgr.addAnimatedMeshSceneNode(mesh, parent, id);
			}
		),
		"addCameraSceneNode", sol::overload(
			[](irr::scene::ISceneManager& smgr) { return smgr.addCameraSceneNode(); },
			[](irr::scene::ISceneManager& smgr, irr::scene::ISceneNode* parent) { return smgr.addCameraSceneNode(parent); }
		),
		"addLightSceneNode", 
			[](irr::scene::ISceneManager& smgr,
				irr::scene::ISceneNode* parent,
				const sol::table& position,
				const sol::table& color,
				irr::f32 radius)
			{ 
				return smgr.addLightSceneNode(parent,
					{ position["x"], position["y"], position["z"] },
					{ color["a"], color["r"], color["g"], color["b"] },
					radius);
			},
		"getSceneCollisionManager", &irr::scene::ISceneManager::getSceneCollisionManager,
		"createTriangleSelector",
			[](irr::scene::ISceneManager& smgr, irr::scene::IAnimatedMeshSceneNode* node) {
				return smgr.createTriangleSelector(node);
			}
	);

	scene.new_usertype<irr::scene::ISceneNode>(
		"ISceneNode", sol::no_constructor,
		"setPosition", [](irr::scene::ISceneNode& node, sol::table pos) { node.setPosition({ pos["x"], pos["y"], pos["z"] }); },
		"getPosition", &irr::scene::ISceneNode::getPosition,
		"getAbsolutePosition", &irr::scene::ISceneNode::getAbsolutePosition,
		"setRotation", [](irr::scene::ISceneNode& node, sol::table rot) { node.setRotation({ rot["x"], rot["y"], rot["z"] }); },
		"updateAbsolutePosition", &irr::scene::ISceneNode::updateAbsolutePosition,
		"setScale", [](irr::scene::ISceneNode& node, sol::table scale) {
			node.setScale({ scale["x"], scale["y"], scale["z"] });
		},
		"getScale", &irr::scene::ISceneNode::getScale,
		"getAbsoluteTransformation", &irr::scene::ISceneNode::getAbsoluteTransformation,
		"setTriangleSelector", &irr::scene::ISceneNode::setTriangleSelector,
		"setID", &irr::scene::ISceneNode::setID,
		"getID", &irr::scene::ISceneNode::getID,
		"setName", sol::resolve<void (const irr::c8*)>(&irr::scene::ISceneNode::setName),
		"getName", &irr::scene::ISceneNode::getName,
		"addAnimator", &irr::scene::ISceneNode::addAnimator,
		"setMaterialFlag", &irr::scene::ISceneNode::setMaterialFlag,
		"setMaterialType", &irr::scene::ISceneNode::setMaterialType
	);

	scene.new_usertype<irr::scene::ICameraSceneNode>(
		"ICameraSceneNode", sol::no_constructor,
		sol::base_classes, sol::bases<irr::scene::ISceneNode>(),
		"bindTargetAndRotation", &irr::scene::ICameraSceneNode::bindTargetAndRotation,
		"setNearValue", &irr::scene::ICameraSceneNode::setNearValue,
		"setTarget", &irr::scene::ICameraSceneNode::setTarget
	);

	scene.new_usertype<irr::scene::IAnimatedMeshSceneNode>(
		"IAnimatedMeshSceneNode", sol::no_constructor,
		sol::base_classes, sol::bases<irr::scene::ISceneNode>(),
		"addShadowVolumeSceneNode", sol::overload(
			[](irr::scene::IAnimatedMeshSceneNode& node) {
				return node.addShadowVolumeSceneNode();
			},
			[](irr::scene::IAnimatedMeshSceneNode& node, irr::scene::IMesh* shadowMesh) {
				return node.addShadowVolumeSceneNode(shadowMesh);
			},
			[](irr::scene::IAnimatedMeshSceneNode& node, irr::scene::IMesh* shadowMesh, irr::s32 id) {
				return node.addShadowVolumeSceneNode(shadowMesh, id);
			},
			[](irr::scene::IAnimatedMeshSceneNode& node, irr::scene::IMesh* shadowMesh, irr::s32 id, bool zfailmethod) {
				return node.addShadowVolumeSceneNode(shadowMesh, id, zfailmethod);
			},
			[](irr::scene::IAnimatedMeshSceneNode& node, irr::scene::IMesh* shadowMesh, irr::s32 id, bool zfailmethod, irr::f32 infinity) {
				return node.addShadowVolumeSceneNode(shadowMesh, id, zfailmethod, infinity);
			}
		)
	);

	scene.new_usertype<irr::scene::ISceneCollisionManager>(
		"ISceneCollisionManager", sol::no_constructor,
		"getSceneNodeAndCollisionPointFromRay", sol::overload(
			[](irr::scene::ISceneCollisionManager& scmgr, irr::core::line3df ray, irr::core::vector3df& outCollisionPoint, irr::core::triangle3df& outTriangle) {
				return scmgr.getSceneNodeAndCollisionPointFromRay(ray, outCollisionPoint, outTriangle);
			},
			[](irr::scene::ISceneCollisionManager& scmgr, irr::core::line3df ray, irr::core::vector3df& outCollisionPoint, irr::core::triangle3df& outTriangle, irr::s32 idBitMask) {
				return scmgr.getSceneNodeAndCollisionPointFromRay(ray, outCollisionPoint, outTriangle, idBitMask);
			})
	);

	scene.new_usertype<irr::scene::ITriangleSelector>(
		"ITriangleSelector", sol::no_constructor,
		"drop", &irr::scene::ITriangleSelector::drop
	);

	return scene;
}