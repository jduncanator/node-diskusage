{
  'targets': [
    {
      'target_name': 'diskusage',
      'include_dirs': [ '<!(node -e "require(\'nan\')")' ],
      'sources': [
        'src/main.cpp',
        'src/diskusage.h',
      ],
      'conditions': [
        ['OS=="win"', {
          'sources': [
            'src/diskusage_win.cpp',
          ],
          'defines': [
            'UNICODE',
            'WIN32_LEAN_AND_MEAN',
            'NOMINMAX'
          ],
          'msvs_settings': {
            'VCCLCompilerTool': {
              'ExceptionHandling': '1'
            }
          }
        }],
        ['OS not in ["win"]', {
          'sources': [
            'src/diskusage_posix.cpp',
          ],
          'cflags!': [ '-fno-exceptions' ],
          'cflags_cc!': [ '-fno-exceptions' ]
        }],
        ['OS=="mac"', {
          'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
          }
        }]
      ]
    }
  ]
}
