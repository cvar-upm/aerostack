function [ line_number_cell ] = searchLineNumWhereStringIsInFile( file_name, wanted_string )
%SEARCHLINENUMWHERESTRINGISINFILE Summary of this function goes here
%   Detailed explanation goes here

line_number_cell = cell(0);

file_read = fopen( file_name,'r');

line_number = 0;
while ~feof(file_read)
    line = fgets(file_read);
    line_number = line_number + 1;
    
    string_is_in_line = regexpi( line, wanted_string);
    if( not(isempty(string_is_in_line)) )
        line_number_cell{end+1} = line_number;
    end
end

fclose(file_read);
end

