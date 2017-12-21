file(REMOVE_RECURSE
  "libMaind.pdb"
  "libMaind.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/Main.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
