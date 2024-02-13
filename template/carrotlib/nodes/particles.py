import raylib as rl
from linalg import vec2, mat3x3
from math import cos, sin, sqrt
from random import random, randint
from typing import Literal

from .._node import Node
from .. import g as _g
from .._renderer import draw_texture, Texture2D, SubTexture2D, draw_rect
from .._colors import Colors
from .._math import clamp, clamp01, lerp

__all__ = ['Particles', 'EmissionShape', 'PointEmissionShape', 'CircleEmissionShape', 'RectEmissionShape', 'EdgeEmissionShape']

class _Particle:
    _time: float

    position: vec2
    rotation: float
    scale: vec2

    lifetime: float
    speed: float
    direction: vec2
    color: rl.Color
    texture: Texture2D | SubTexture2D | None

    @property
    def velocity(self) -> vec2:
        self.direction.normalize_()
        return self.direction * self.speed


class EmissionShape:
    def sample(self, rotation: float) -> tuple[vec2, vec2]:
        """Sample a point from the shape. Return the position and the direction."""
        raise NotImplementedError
    
    @staticmethod
    def random_direction() -> vec2:
        theta = random() * 2 * 3.141592653589793
        return vec2(cos(theta), sin(theta))

class PointEmissionShape(EmissionShape):
    def sample(self, rotation: float) -> tuple[vec2, vec2]:
        return vec2(0, 0), self.random_direction()

class CircleEmissionShape(EmissionShape):
    def __init__(self, radius: float, solid=True):
        self.solid = solid
        self.radius = radius

    def sample(self, rotation: float) -> tuple[vec2, vec2]:
        if self.solid:
            r = self.radius * sqrt(random())
        else:
            r = self.radius
        theta = random() * 2 * 3.141592653589793
        return vec2(r*cos(theta), r*sin(theta)), self.random_direction()

class RectEmissionShape(EmissionShape):
    def __init__(self, hx: float, hy: float, solid=True):
        self.solid = solid
        self.hx = hx
        self.hy = hy

    def sample(self, rotation: float) -> tuple[vec2, vec2]:
        if self.solid:
            x = (random() - 0.5) * self.hx
            y = (random() - 0.5) * self.hy
        else:
            raise NotImplementedError
        return vec2(x, y).rotate(rotation), vec2(0, 0)
    
class EdgeEmissionShape(EmissionShape):
    def __init__(self, hx: float):
        self.hx = hx

    def sample(self, rotation: float) -> tuple[vec2, vec2]:
        x = (random() - 0.5) * self.hx
        return vec2(x, 0).rotate(rotation), vec2(0, -1).rotate(rotation)


def _float(value: float | tuple[float, float]):
    if isinstance(value, (int, float)):
        return value * 1.0
    a, b = value
    if a < b:
        return a + random() * (b - a)
    else:
        return b + random() * (a - b)

def _int(value: int | tuple[int, int]):
    if isinstance(value, int):
        return value
    a, b = value
    if a < b:
        return randint(a, b)
    else:
        return randint(b, a)

def _color(value: rl.Color | tuple[rl.Color, rl.Color]):
    if isinstance(value, rl.Color):
        return value
    a, b = value
    return rl.Color(
        _int((a.r, b.r)),
        _int((a.g, b.g)),
        _int((a.b, b.b)),
        _int((a.a, b.a)),
    )

def _vec2(value: vec2 | tuple[vec2, vec2]):
    if isinstance(value, vec2):
        return value
    a, b = value
    return vec2(
        _float((a.x, b.x)),
        _float((a.y, b.y)),
    )

class Particles(Node):
    _particles: list[_Particle]

    shape: EmissionShape

    def __init__(self, name=None, parent=None):
        super().__init__(name=name, parent=parent)

        self._particles = []

        self.duration = 5
        self.looping = True

        self.start_lifetime = 5.0
        self.start_speed = 5.0
        self.start_scale = vec2(1, 1)
        self.start_rotation = 0.0
        self.start_color = Colors.White
        self.start_texture = None

        self.max_particles = 1000
        # self.simulation_speed = 1.0

        self.play_on_ready = True

        # Emission Shape
        self.rate_over_time = 10
        self.shape = PointEmissionShape()

        # Curves
        self.color_over_lifetime = None
        self.scale_over_lifetime = None

        self._coroutine = None
    
    def play(self):
        self._coroutine = self.start_coroutine(self._emit_coroutine())

    def stop(self):
        if self._coroutine is not None:
            self.stop_coroutine(self._coroutine)
            self._coroutine = None

    def on_ready(self):
        if self.play_on_ready:
            self.play()

    def on_render(self):
        t = mat3x3.identity()
        self_t = self.transform()
        self_t.copy_r_(0)   # reset rotation
        for p in self._particles:
            t.copy_trs_(p.position, p.rotation, p.scale)
            self_t.matmul(t, out=t)
            if p.texture is not None:
                draw_texture(t, p.texture, color=p.color)

    def _emit_coroutine(self):
        while True:
            now = rl.GetTime()
            # emit one cycle of particles
            E = self.rate_over_time * self.duration
            times = [now + random() * self.duration for _ in range(E)]
            times.sort(reverse=True)
            
            while times:
                now = rl.GetTime()
                delta = rl.GetFrameTime()
                self_t = self.transform()

                # remove dead particles
                self._particles = [p for p in self._particles if now-p._time<p.lifetime]
                # update
                for p in self._particles:
                    p.position += p.velocity * delta
                    value = 1 - clamp01((now - p._time) / p.lifetime)
                    if self.scale_over_lifetime:
                        p.scale = self.scale_over_lifetime(value)
                    if self.color_over_lifetime:
                        p.color = self.color_over_lifetime(value)

                if now >= times[-1]:
                    times.pop()
                    if len(self._particles) < self.max_particles:
                        p = _Particle()
                        p._time = now
                        p.position, p.direction = self.shape.sample(self_t._r())
                        p.rotation = _float(self.start_rotation)

                        if self.scale_over_lifetime:
                            p.scale = self.scale_over_lifetime(1)
                        else:
                            p.scale = _vec2(self.start_scale)

                        p.lifetime = _float(self.start_lifetime)
                        p.speed = _float(self.start_speed)

                        if self.color_over_lifetime:
                            p.color = self.color_over_lifetime(1)
                        else:
                            p.color = _color(self.start_color)
                            
                        p.texture = self.start_texture
                        self._particles.append(p)
                yield None

            if not self.looping:
                break

