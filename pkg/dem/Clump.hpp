#pragma once
#include<woo/pkg/dem/Particle.hpp>
#include<woo/lib/sphere-pack/SpherePack.hpp>
#include<woo/pkg/dem/ShapePack.hpp>
#include<woo/lib/pyutil/converters.hpp>


struct SphereClumpGeom: public ShapeClump {
	WOO_DECL_LOGGER;
	void postLoad(SphereClumpGeom&,void*);
	// may fail when called from postLoad, but not from ensureOk()
	void recompute(int div, bool failOk=false, bool fastOnly=false) WOO_CXX11_OVERRIDE;
	void makeInvalid(){ volume=equivRad=NaN; inertia=Vector3r(NaN,NaN,NaN); pos=Vector3r::Zero(); ori=Quaternionr::Identity(); }
	bool isOk() const { return !isnan(volume); }
	void ensureOk() { if(!isOk()) recompute(div,/*failOk*/false); }
	std::tuple<vector<shared_ptr<Node>>,vector<shared_ptr<Particle>>> makeParticles(const shared_ptr<Material>&, const Vector3r& pos, const Quaternionr& ori, int mask, Real scale=1.) WOO_CXX11_OVERRIDE;
	// void ensureApproxPos() WOO_CXX11_OVERRIDE;
	static vector<shared_ptr<SphereClumpGeom>> fromSpherePack(const shared_ptr<SpherePack>& sp, int div=5);

	void translate(const Vector3r& offset) WOO_CXX11_OVERRIDE;
	shared_ptr<ShapeClump> copy() const WOO_CXX11_OVERRIDE;

	#define woo_dem_SphereClumpGeom__CLASS_BASE_DOC_ATTRS_PY \
		SphereClumpGeom,ShapeClump,"Defines geometry of spherical clumps. Each clump is described by spheres it is made of (position and radius).", \
		((vector<Vector3r>,centers,,AttrTrait<Attr::triggerPostLoad>(),"Centers of constituent spheres, in clump-local coordinates.")) \
		((vector<Real>,radii,,AttrTrait<Attr::triggerPostLoad>(),"Radii of constituent spheres")) \
		, /* py */ \
		.def("fromSpherePack",&SphereClumpGeom::fromSpherePack,(py::arg("pack"),py::arg("div")=5),"Return [ :obj:`SphereClumpGeom` ] which contain all clumps and spheres from given :obj:`SpherePack`.").staticmethod("fromSpherePack") \
		; woo::converters_cxxVector_pyList_2way<shared_ptr<SphereClumpGeom>>();


	WOO_DECL__CLASS_BASE_DOC_ATTRS_PY(woo_dem_SphereClumpGeom__CLASS_BASE_DOC_ATTRS_PY);
};
WOO_REGISTER_OBJECT(SphereClumpGeom);



struct ClumpData: public DemData{
	static shared_ptr<Node> makeClump(const vector<shared_ptr<Node>>& nodes, shared_ptr<Node> centralNode=shared_ptr<Node>(), bool intersecting=false);
	// sum forces and torques from members; does not touch our data, adds to passed references F, T
	// only the integrator should modify DemData.{force,torque} directly
	static py::tuple pyForceTorqueFromMembers(const shared_ptr<Node>& node);
	static void forceTorqueFromMembers(const shared_ptr<Node>& node, Vector3r& F, Vector3r& T);
	// update member's positions and velocities
	static void applyToMembers(const shared_ptr<Node>&, bool resetForceTorque=false);
	static void resetForceTorque(const shared_ptr<Node>&);

	WOO_DECL_LOGGER;
	#define woo_dem_ClumpData__CLASS_BASE_DOC_ATTRS_PY \
		ClumpData,DemData,"Data of a DEM particle which binds multiple particles together.", \
		((vector<shared_ptr<Node>>,nodes,,AttrTrait<Attr::readonly>().noGui(),"Member nodes")) \
		((vector<Vector3r>,relPos,,AttrTrait<Attr::readonly>(),"Relative member's positions")) \
		((vector<Quaternionr>,relOri,,AttrTrait<Attr::readonly>(),"Relative member's orientations")) \
		((Real,equivRad,NaN,,"Equivalent radius, for PSD statistics (e.g. in :obj:`BoxOutlet`).")) \
		,/*py*/ .def("forceTorqueFromMembers",&ClumpData::pyForceTorqueFromMembers,"Return the tuple (F,T), summary force and torque values collected from clump members, as acting on the clump node passed as argument.").staticmethod("forceTorqueFromMembers")
	WOO_DECL__CLASS_BASE_DOC_ATTRS_PY(woo_dem_ClumpData__CLASS_BASE_DOC_ATTRS_PY);
};
WOO_REGISTER_OBJECT(ClumpData);

