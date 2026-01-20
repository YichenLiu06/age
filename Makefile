CACHE = gcm.cache/
CXX = /usr/local/bin/g++-15.2.0
CXXFLAGS = -std=c++20 -fmodules-ts -Wall -MMD -lncursesw -g
CXXHFLAGS = -std=c++20 -fmodules-ts -c -x c++-system-header
EXEC = age
HEADERS = $(CACHE)iostream.gcm \
          $(CACHE)vector.gcm \
          $(CACHE)chrono.gcm \
          $(CACHE)memory.gcm \
          $(CACHE)algorithm.gcm \
          $(CACHE)map.gcm \
          $(CACHE)utility.gcm \
          $(CACHE)variant.gcm \
          $(CACHE)cmath.gcm \
          $(CACHE)string.gcm \
          $(CACHE)ranges.gcm \
          $(CACHE)queue.gcm \
          $(CACHE)cstdlib.gcm \
          $(CACHE)initializer_list.gcm \
          

OBJECTS = eventqueue.o \
          eventqueue-impl.o \
          textstatus.o \
          textstatus-impl.o \
          vector3d.o \
          vector3d-impl.o \
          controller.o \
          cursescontroller.o \
          cursescontroller-impl.o \
          gameobjectcomponent.o \
          gameobjectcomponent-impl.o \
          clonablecomponent.o \
          state.o \
          state-impl.o \
          transform.o \
          transform-impl.o \
          clampedtransform.o \
          clampedtransform-impl.o \
          timer.o \
          timer-impl.o \
          movement.o \
          movement-impl.o \
          collider.o \
          boxcollider.o \
          boxcollider-impl.o \
          collisionbehaviour.o \
          stopcollisionbehaviour.o \
          stopcollisionbehaviour-impl.o \
          bouncecollisionbehaviour.o \
          bouncecollisionbehaviour-impl.o \
          boxtexture.o \
          boxtexture-impl.o \
		  pixel.o \
		  pixel-impl.o \
		  bitmaptexture.o \
		  bitmaptexture-impl.o \
		  sprite.o \
		  sprite-impl.o \
          inputhandler.o \
          eventhandler.o \
          spawner.o \
          spawner-impl.o \
		  view.o \
		  cursesview.o \
		  cursesview-impl.o \
          gameobjectmanager.o \
          gameobjectmanager-impl.o \
          inputsystem.o \
          inputsystem-impl.o \
		  movementsystem.o \
		  movementsystem-impl.o \
          collisionsystem.o \
          collisionsystem-impl.o \
          timersystem.o \
          timersystem-impl.o \
          spawnsystem.o \
          spawnsystem-impl.o \
          eventsystem.o \
          eventsystem-impl.o \
		  graphicssystem.o \
		  graphicssystem-impl.o \
		  world.o \
		  world-impl.o \
          pong.o \
          flappybird.o \
		  main.o \

DEPENDS = ${OBJECTS:.o=.d}

main: $(HEADERS) ${OBJECTS}
	${CXX} ${OBJECTS} ${GIVEN} -o ${EXEC} ${CXXFLAGS}

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.gcm:
	$(CXX) $(CXXHFLAGS) $(patsubst $(CACHE)%.gcm,%,$@)

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS} ./gcm.cache/*.gcm
    