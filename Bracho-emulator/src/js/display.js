// const display = ref(Array(64).fill(Array(64).fill(0)))

export function praseDisplayOUT(input) {
    let color = input & 0b1111;
    let y = (input & 0b1111110000) >> 4;
    let x = (input & 0b1111110000000000) >> 10;

    return {"color": color, "x": x, "y": y}
}