const std = @import("std");
const sdl = @cImport({
    @cInclude("SDL2/SDL.h");
});

pub fn main() !void {
    std.debug.print("{d}\n", .{sdl.SDL_Init(0)});
}
