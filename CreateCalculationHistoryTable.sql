CREATE TABLE CalculationHistory (
    Id INT PRIMARY KEY IDENTITY(1,1),
    Calculation NVARCHAR(MAX),
    Result NVARCHAR(MAX),
    Timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
);
