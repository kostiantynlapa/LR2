use std::time::Instant;

fn det(matrix: &Vec<Vec<i32>>) -> i32 {
    let n = matrix.len();
    
    if n == 1 {
        return matrix[0][0];
    }
    
    if n == 2 {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    
    let mut total = 0;
    for c in 0..n {
        let mut sub: Vec<Vec<i32>> = vec![vec![0; n - 1]; n - 1];
        
        for i in 1..n {
            let mut k = 0;
            for j in 0..n {
                if j != c {
                    sub[i - 1][k] = matrix[i][j];
                    k += 1;
                }
            }
        }
        
        let sign = if c % 2 == 0 { 1 } else { -1 };
        total += sign * matrix[0][c] * det(&sub);
    }
    
    total
}

fn main() {
    // Матриця для тестування
    let matrix: Vec<Vec<i32>> = vec![
        vec![3, 1, 3, 5, 8],
        vec![1, 8, 6, 6, 7],
        vec![1, 7, 6, 6, 1],
        vec![3, 8, 8, 2, 8],
        vec![6, 9, 7, 9, 3],
    ];

    println!("=== Rust Implementation ===");
    println!("Matrix (5x5):");
    for row in &matrix {
        for val in row {
            print!("{} ", val);
        }
        println!();
    }

    let start_time = Instant::now();
    
    let mut determinant = 0;
    for _i in 0..10000 {
        determinant = det(&matrix);
    }
    
    let elapsed = start_time.elapsed();

    println!("\nDeterminant: {}", determinant);
    println!("Time for 10000 computations: {:.6} seconds", elapsed.as_secs_f64());
    println!("Average time per computation: {:.2} microseconds", 
             (elapsed.as_secs_f64() / 10000.0) * 1_000_000.0);
}
