# Editor Cameras

This camera setup has no affiliation with the ECS system. These are some general purpose free roaming cameras mainly used in the editor. They are created
in the engine, because some games may have a unique use case for them such as a spectator camera or something that doesn't really care about being an
actual entity. Some values in the Camera Settings are slightly redundant between Perspective and Orthographic, however I feel as though a couple extra bytes
is the least problematic issues regarding this engine. So, out of simplicity I just combined all settings to make it easier to adjust them in the editor.