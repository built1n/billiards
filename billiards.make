#             __________               __   ___.
#   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
#   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
#   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
#   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
#                     \/            \/     \/    \/            \/
# $Id$
#

BILLIARDSSRCDIR := $(APPSDIR)/plugins/billiards
BILLIARDSBUILDDIR := $(BUILDDIR)/apps/plugins/billiards

ROCKS += $(BILLIARDSBUILDDIR)/billiards.rock

BILLIARDS_SRC := $(call preprocess, $(BILLIARDSSRCDIR)/SOURCES)
BILLIARDS_OBJ := $(call c2obj, $(BILLIARDS_SRC))

# add source files to OTHER_SRC to get automatic dependencies
OTHER_SRC += $(BILLIARDS_SRC)

BILLIARDSFLAGS = $(filter-out -O%,$(PLUGINFLAGS)) -O2 -Iplatforms/rockbox -Isrc

$(BILLIARDSBUILDDIR)/billiards.rock: $(BILLIARDS_OBJ)

$(BILLIARDSBUILDDIR)/%.o: $(BILLIARDSSRCDIR)/%.c $(BILLIARDSSRCDIR)/billiards.make
	$(SILENT)mkdir -p $(dir $@)
	$(call PRINTS,CC $(subst $(ROOTDIR)/,,$<))$(CC) -I$(dir $<) $(BILLIARDSFLAGS) -c $< -o $@
