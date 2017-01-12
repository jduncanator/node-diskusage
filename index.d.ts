type DiskUsage = {
    available: number;
    free: number;
    total: number;
}

export function check(path: string, callback: (error: Error, result: DiskUsage) => void): void;
export function checkSync(path: string): DiskUsage;
