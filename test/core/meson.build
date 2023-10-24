car = files('car.c')
cdr = files('cdr.c')
cons = files('cons.c')
read = files('read.c')
reverse = files('reverse.c')

tests += car + cdr + cons + read + reverse

test('core_car', executable('car',
  build_by_default: false,
  dependencies: [bdwgc],
  include_directories: include,
  sources: [sources, car]
))

test('core_cdr', executable('cdr',
  build_by_default: false,
  dependencies: [bdwgc],
  include_directories: include,
  sources: [sources, cdr]
))

test('core_cons', executable('cons',
  build_by_default: false,
  dependencies: [bdwgc],
  include_directories: include,
  sources: [sources, cons]
))

test('core_read', executable('read',
  build_by_default: false,
  dependencies: [bdwgc],
  include_directories: include,
  sources: [sources, read]
))

test('core_reverse', executable('reverse',
  build_by_default: false,
  dependencies: [bdwgc],
  include_directories: include,
  sources: [sources, reverse]
))
