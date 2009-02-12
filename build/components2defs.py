# $Id$
# Generates the contents of "components_defs.mk".

from components import checkComponents, coreLibs
from makeutils import extractMakeVariables

import sys

def iterComponentDefs(probeMakePath):
	probeVars = extractMakeVariables(probeMakePath)
	buildCore, buildGL, buildJack = checkComponents(probeVars)

	yield '# Automatically generated by build process.'
	yield 'CORE_LIBS:=%s' % ' '.join(coreLibs)
	yield 'COMPONENT_CORE:=%s' % str(buildCore).lower()
	yield 'COMPONENT_GL:=%s' % str(buildGL).lower()
	yield 'COMPONENT_JACK:=%s' % str(buildJack).lower()

if len(sys.argv) == 2:
	probeMakePath = sys.argv[1]
	for line in iterComponentDefs(probeMakePath):
		print line
else:
	print >>sys.stderr, (
		'Usage: python components2defs.py PROBE_MAKE'
		)
	sys.exit(2)