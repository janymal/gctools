project(
    'gctools',
    'cpp',
    default_options: ['default_library=static', 'cpp_std=c++20', 'werror=true'],
)

cpp = meson.get_compiler('cpp')

if cpp.get_argument_syntax() == 'gcc'
    add_project_arguments(
        cpp.get_supported_arguments(
            [
                '-Wno-strict-aliasing',
            ],
        ),
        language: 'cpp',
    )
endif

phosg_dep = dependency('phosg', fallback: ['phosg', 'phosg_dep'])
phosg_audio_dep = dependency(
    'phosg-audio',
    fallback: ['phosg', 'phosg_audio_dep'],
)
openal_dep = dependency('OpenAL')
samplerate_dep = dependency('samplerate')

prs = library(
    'prs',
    'src/prs/PRSDataLog.cc',
    'src/prs/PRS.cc',
    'src/prs/Yay0.cc',
    'src/prs/Yaz0.cc',
    dependencies: [phosg_dep],
    install: true,
)

install_headers(
    'src/prs/PRS.hh',
    'src/prs/PRSDataLog.hh',
    'src/prs/Yay0.hh',
    'src/prs/Yaz0.hh',
    subdir: 'prs',
)

simple_executable_names = [
    'afsdump',
    'gcmasm',
    'gcmdump',
    'gsldump',
    'gvmdump',
    'rcfdump',
]
all_executable_names = [
    simple_executable_names,
    'pae2gvm',
    'prsd',
    'smsdumpbanks',
    'smssynth',
    'modsynth',
]

foreach executable_name : simple_executable_names
    executable(
        executable_name,
        f'src/@executable_name@.cc',
        dependencies: [phosg_dep],
        install: true,
    )
endforeach

executable(
    'pae2gvm',
    'src/pae2gvm.cc',
    dependencies: [phosg_dep],
    link_with: [prs],
    install: true,
)

executable(
    'prsd',
    'src/prs/main.cc',
    dependencies: [phosg_dep],
    link_with: [prs],
    install: true,
)

executable(
    'smsdumpbanks',
    'src/sms/smsdumpbanks.cc',
    'src/sms/aaf.cc',
    'src/sms/afc.cc',
    'src/sms/instrument.cc',
    dependencies: [phosg_dep, phosg_audio_dep, openal_dep],
    link_with: [prs],
    install: true,
)

executable(
    'smssynth',
    'src/sms/smssynth.cc',
    'src/sms/SampleCache.cc',
    'src/sms/aaf.cc',
    'src/sms/afc.cc',
    'src/sms/instrument.cc',
    dependencies: [phosg_dep, phosg_audio_dep, openal_dep, samplerate_dep],
    link_with: [prs],
    install: true,
)

executable(
    'modsynth',
    'src/sms/modsynth.cc',
    'src/sms/SampleCache.cc',
    dependencies: [phosg_dep, phosg_audio_dep, openal_dep, samplerate_dep],
    link_with: [prs],
    install: true,
)
