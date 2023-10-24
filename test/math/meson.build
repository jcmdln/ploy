add = files('add.c')
divide = files('divide.c')
multiply = files('multiply.c')
subtract = files('subtract.c')

tests += add + divide + multiply + subtract

test('math_add', executable('add',
  build_by_default: false,
  dependencies: [bdwgc],
  include_directories: include,
  sources: [sources, add]
))

test('math_divide', executable('divide',
  build_by_default: false,
  dependencies: [bdwgc],
  include_directories: include,
  sources: [sources, divide]
))

test('math_multiply', executable('multiply',
  build_by_default: false,
  dependencies: [bdwgc],
  include_directories: include,
  sources: [sources, multiply]
))

test('math_subtract', executable('subtract',
  build_by_default: false,
  dependencies: [bdwgc],
  include_directories: include,
  sources: [sources, subtract]
))
