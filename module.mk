# Copyright 2015 Erik Van Hamme
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

sources += \
	ecppstm32/src/syscalls.c \

headers += \
	ecppstm32/inc/gpio.h \
	ecppstm32/inc/rcc.h \
	ecppstm32/inc/stm32_traits.h \
	ecppstm32/inc/stm32_types.h \
	ecppstm32/inc/timer.h \

