'''Define various convenience attributes, such as ``Node.dem`` for accessing DEM data of a node (equivalent to ``node->getData<DemData>()`` in c++).'''

from woo import core
from woo.core import Master
core.Field.nod=core.Field.nodes

## proxy for attribute-like access to Scene.labels
## http://stackoverflow.com/questions/16061041/proxy-class-for-accessing-other-class-items-as-attributes-getitem-infinite
class LabelMapperProxy(object):
	def __init__(self,scene): self.__dict__['_scene']=scene
	def __getattr__(self,key): return self._scene.labels[key]
	def __setattr__(self,key,val): self._scene.labels[key]=val
	def __delattr__(self,key): del self._scene.labels[key]
def Scene_lab(scene):
	return LabelMapperProxy(scene)
core.Scene.lab=property(Scene_lab)


try:
	from woo import dem
	dem.DemField.par=dem.DemField.particles
	dem.DemField.con=dem.DemField.contacts
	dem.Particle.mat=dem.Particle.material
	core.Scene.dem=property(lambda s: dem.DemField.sceneGetField(s))
	core.Scene.hasDem=property(lambda s: dem.DemField.sceneHasField(s))
	def _Master_dem(o): raise ValueError("Master.dem is no longer supported, use Scene.dem instead")
	def _Master_hasDem(o): raise ValueError("Master.hasDem is no longer supported, use Scene.hasDem instead")
	core.Master.dem=property(_Master_dem)
	core.Master.hasdem=property(_Master_hasDem)
	# DemData defines those methods, which are used for transparent access to respective data field
	core.Node.dem=property(dem.DemData._getDataOnNode,dem.DemData._setDataOnNode)
	# this can be removed later
	def _DemData_parCount_get(d): raise AttributeError("DemData.parCount is superceded by DemData.parRef!")
	def _DemData_parCount_set(d): raise AttributeError("DemData.parCount is superceded by DemData.parRef!")
	dem.DemData.parCount=property(_DemData_parCount_get,_DemData_parCount_set)
except ImportError:
	core.Scene.hasDem=lambda o: False

try:
	from woo import sparc
	core.Scene.sparc=property(lambda s: sparc.SparcField.sceneGetField(s))
	core.Scene.hasSparc=property(lambda s: sparc.SparcField.sceneHasField(s))
	core.Node.sparc=property(sparc.SparcData._getDataOnNode,sparc.SparcData._setDataOnNode)
except ImportError:
	core.Scene.hasSparc=lambda o: False


try:
	import woo.cld
	core.Scene.clDem=property(lambda s: cld.CLDemField.sceneGetField(s))
	core.Scene.hasClDem=property(lambda s: woo.clDem.CLDemField.sceneHasField(s))
	core.Node.clDem=property(woo.cld.CLDemData._getDataOnNode,woo.cld.CLDemData._setDataOnNode)
except ImportError:
	core.Scene.hasClDem=lambda o: False


try:
	from woo import gl
	core.Node.gl=property(gl.GlData._getDataOnNode,gl.GlData._setDataOnNode)
except ImportError: pass

#try:
#	from woo import ancf
#	core.Node.ancf=property(ancf.AncfData._getDataOnNode,ancf.AncfData._setDataOnNode)
#except ImportError: pass
